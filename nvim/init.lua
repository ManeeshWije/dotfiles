-- opts
vim.g.mapleader = ","
vim.g.maplocalleader = ","
vim.g.loaded_netrw = 1
vim.g.loaded_netrwPlugin = 1
vim.opt.guicursor = ""
vim.opt.number = true
vim.opt.relativenumber = true
vim.opt.mouse = "a"
vim.opt.clipboard = "unnamedplus"
vim.opt.breakindent = true
vim.opt.undofile = true
vim.opt.ignorecase = true
vim.opt.smartcase = true
vim.opt.signcolumn = "yes"
vim.opt.updatetime = 250
vim.opt.timeoutlen = 300
vim.opt.scrolloff = 10
vim.opt.sidescrolloff = 10
vim.opt.hlsearch = true
vim.opt.tabstop = 4
vim.opt.softtabstop = 4
vim.opt.shiftwidth = 4
vim.opt.expandtab = true
vim.opt.smartindent = true
vim.opt.termguicolors = true
vim.opt.wrap = false
vim.opt.previewheight = 25
vim.opt.fillchars = { fold = " " }
vim.opt.foldmethod = "indent"
vim.opt.foldenable = false
vim.opt.foldlevel = 99
vim.g.markdown_folding = 1
vim.cmd ([[
augroup remember_folds
  autocmd!
  au BufWinLeave ?* mkview 1
  au BufWinEnter ?* silent! loadview 1
augroup END
]])

vim.api.nvim_create_augroup("vimStartup", { clear = true })
vim.api.nvim_create_autocmd("BufReadPost", {
    group = "vimStartup",
    callback = function()
        local last_position = vim.fn.line([['"]])
        local last_line = vim.fn.line("$")
        local filetype = vim.bo.filetype

        if last_position >= 1 and last_position <= last_line and not filetype:match("commit") then
            vim.cmd('normal! g`"')
        end
    end,
})
vim.api.nvim_create_autocmd("TextYankPost", {
    desc = "Highlight when yanking (copying) text",
    group = vim.api.nvim_create_augroup("highlight-yank", { clear = true }),
    callback = function()
        vim.highlight.on_yank()
    end,
})

-- Lazy
local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
if not vim.loop.fs_stat(lazypath) then
    local lazyrepo = "https://github.com/folke/lazy.nvim.git"
    vim.fn.system({ "git", "clone", "--filter=blob:none", "--branch=stable", lazyrepo, lazypath })
end
vim.opt.rtp:prepend(lazypath)

require("lazy").setup({
    { -- LSP Configuration & Plugins
        "neovim/nvim-lspconfig",
        dependencies = {
            "williamboman/mason.nvim",
            { "j-hui/fidget.nvim", opts = {} },
            {
                "folke/lazydev.nvim",
                opts = {
                    library = {
                        { path = "${3rd}/luv/library", words = { "vim%.uv" } },
                    },
                },
            },
        },
        opts = {
            servers = {
                clangd = {},
                gopls = {},
                basedpyright = {
                    settings = {
                        basedpyright = {
                            analysis = {
                                typeCheckingMode = "standard",
                            },
                        },
                    },
                },
                rust_analyzer = {},
                ts_ls = {},
                bashls = {},
                cssls = {},
                dockerls = {},
                emmet_ls = {},
                eslint = {},
                html = {},
                jdtls = {},
                jsonls = {},
                phpactor = {},
                sqlls = {},
                tailwindcss = {},
                lua_ls = {},
                helm_ls = {},
            },
        },
        config = function(_, opts)
            require("mason").setup()
            for server, config in pairs(opts.servers) do
                config.capabilities = vim.lsp.protocol.make_client_capabilities()
                require("lspconfig")[server].setup(config)
            end
            vim.api.nvim_create_autocmd("LspAttach", {
                group = vim.api.nvim_create_augroup("lsp-attach", { clear = true }),
                callback = function(event)
                    local client = vim.lsp.get_client_by_id(event.data.client_id)
                    if client and client.server_capabilities.documentHighlightProvider then
                        vim.api.nvim_create_autocmd({ "CursorHold", "CursorHoldI" }, {
                            buffer = event.buf,
                            callback = vim.lsp.buf.document_highlight,
                        })
                        vim.api.nvim_create_autocmd({ "CursorMoved", "CursorMovedI" }, {
                            buffer = event.buf,
                            callback = vim.lsp.buf.clear_references,
                        })
                    end
                end,
            })
        end,
    },

    { -- Autoformat
        "stevearc/conform.nvim",
        opts = {
            notify_on_error = true,
            formatters_by_ft = {
                lua = { "stylua" },
                python = { "isort", "black" },
                javascript = { "prettier" },
                typescript = { "prettier" },
                javascriptreact = { "prettier" },
                typescriptreact = { "prettier" },
                java = { "google-java-format" },
                go = { "gofmt", "goimports" },
                rust = { "rustfmt" },
                php = { "php-cs-fixer" },
                c = { "clang-format" },
                markdown = { "prettier" },
                sql = { "sql_formatter" },
                html = { "prettier" },
            },
            formatters = {
                sql_formatter = {
                    command = "sql-formatter",
                    args = { "--language", "postgresql" },
                },
            },
        },
    },

    { -- Autocompletion
        "saghen/blink.cmp",
        dependencies = {
            "L3MON4D3/LuaSnip",
            version = "v2.*",
            dependencies = {
                "rafamadriz/friendly-snippets",
                config = function()
                    require("luasnip.loaders.from_vscode").lazy_load()
                end,
            },
        },
        version = "*",
        opts = {
            completion = {
                menu = {
                    border = "single",
                    winhighlight = "Normal:BlinkCmpDoc,FloatBorder:BlinkCmpDocBorder,CursorLine:BlinkCmpMenuSelection,Search:None",
                },
                documentation = {
                    window = {
                        border = "single",
                    },
                    auto_show = true,
                    auto_show_delay_ms = 50,
                },
            },
            signature = {
                window = {
                    border = "single",
                },
                enabled = true,
            },
            keymap = {
                preset = "default",
                ["<c-k>"] = { "scroll_documentation_up", "fallback" },
                ["<c-j>"] = { "scroll_documentation_down", "fallback" },
            },
            cmdline = {
                enabled = false
            },
            sources = {
                default = { "lsp", "path", "snippets", "buffer", "dadbod" },
                providers = {
                    dadbod = {
                        name = "dadbod",
                        module = "vim_dadbod_completion.blink",
                        score_offset = 85,
                    },
                },
            },
        },
    },

    { -- Install LSP's
        "williamboman/mason.nvim",
    },

    { -- Colourscheme
        "RRethy/base16-nvim"
    },

    { -- Highlight, edit, and navigate code
        "nvim-treesitter/nvim-treesitter",
        build = ":TSUpdate",
        config = function()
            require("nvim-treesitter.configs").setup({
                ensure_installed = "all",
                auto_install = true,
                sync_install = false,
                highlight = { enable = true },
                indent = { enable = true },
            })
        end,
    },

    { -- Jump to project files
        "ThePrimeagen/harpoon",
        branch = "harpoon2",
        dependencies = { "nvim-lua/plenary.nvim" },
        opts = {},
    },

    { -- Auto Pairs
        "windwp/nvim-autopairs",
        event = "InsertEnter",
        config = true,
    },

    { -- Markdown Preview
        "iamcco/markdown-preview.nvim",
        cmd = { "MarkdownPreviewToggle", "MarkdownPreview", "MarkdownPreviewStop" },
        build = "cd app && yarn install",
        init = function()
            vim.g.mkdp_filetypes = { "markdown" }
        end,
        ft = { "markdown" },
    },

    { -- SQL interface
        "tpope/vim-dadbod",
    },

    { -- DB UI
        "kristijanhusak/vim-dadbod-ui",
        dependencies = {
            { "tpope/vim-dadbod", lazy = true },
            { "kristijanhusak/vim-dadbod-completion", ft = { "sql", "mysql", "plsql" }, lazy = true },
        },
        cmd = {
            "DBUI",
            "DBUIToggle",
            "DBUIAddConnection",
            "DBUIFindBuffer",
        },
        init = function()
            vim.g.db_ui_use_nerd_fonts = 1
        end,
    },

    { -- Access yazi
        "rolv-apneseth/tfm.nvim",
        config = function()
            vim.api.nvim_set_keymap("n", "<leader>e", "", {
                noremap = true,
                callback = require("tfm").open,
            })
        end,
    },

    {  -- Surround
        'echasnovski/mini.surround', version = false
    },

    { -- QOL
        "folke/snacks.nvim",
        priority = 1000,
        lazy = false,
        ---@type snacks.Config
        opts = {
            picker = { enabled = true },
            bigfile = { enabled = true },
            indent = { enabled = true },
            image = { enabled = true },
            input = { enabled = true },
            notifier = { enabled = true },
            quickfile = { enabled = true },
            words = { enabled = true },
            git = { enabled = true },
            gitbrowse = { enabled = true },
        },
        keys = {
            -- find
            { "<leader>fb", function() Snacks.picker.buffers() end, desc = "Buffers", },
            { "<leader>ff", function() Snacks.picker.files({ ignored = true }) end, desc = "Find Files", },
            { "<leader>fg", function() Snacks.picker.git_files() end, desc = "Find Git Files", },
            { "<leader>fr", function() Snacks.picker.recent() end, desc = "Recent", },
            { "<leader>fu", function() Snacks.picker.undo() end, desc = "Undo", },
            -- git
            { "<leader>gl", function() Snacks.picker.git_log() end, desc = "Git Log", },
            { "<leader>gs", function() Snacks.picker.git_status() end, desc = "Git Status", },
            { "<leader>gB", function() Snacks.gitbrowse() end, desc = "Git Browse", mode = { "n", "v" }, },
            { "<leader>gb", function() Snacks.git.blame_line() end, desc = "Git Blame Line", },
            -- Grep
            { "<leader>sb", function() Snacks.picker.grep_buffers() end, desc = "Grep Open Buffers", },
            { "<leader>sg", function() Snacks.picker.grep() end, desc = "Grep", },
            { "<leader>sw", function() Snacks.picker.grep_word() end, desc = "Visual selection or word", mode = { "n", "x" }, },
            -- search
            { "<leader>sd", function() Snacks.picker.diagnostics_buffer() end, desc = "Diagnostics Buffer", },
            { "<leader>sD", function() Snacks.picker.diagnostics() end, desc = "Diagnostics", },
            { "<leader>sh", function() Snacks.picker.help() end, desc = "Help Pages", },
            { "<leader>sm", function() Snacks.picker.man() end, desc = "Man Pages", },
            -- LSP
            { "gd", function() Snacks.picker.lsp_definitions() end, desc = "Goto Definition", },
            { "gD", function() Snacks.picker.lsp_declarations() end, desc = "Goto Declaration", },
            { "gr", function() Snacks.picker.lsp_references() end, nowait = true, desc = "References", },
            { "gI", function() Snacks.picker.lsp_implementations() end, desc = "Goto Implementation", },
            { "gy", function() Snacks.picker.lsp_type_definitions() end, desc = "Goto T[y]pe Definition", },
            { "<leader>ss", function() Snacks.picker.lsp_symbols() end, desc = "LSP Symbols", },
            -- Misc
            { "<leader>sp", function() Snacks.picker.spelling() end, desc = "Spelling", },
        },
    },

    {
      "supermaven-inc/supermaven-nvim",
      config = function()
        require("supermaven-nvim").setup({})
      end,
    }
})

vim.keymap.set("i", "jk", "<Esc>")
vim.keymap.set("n", "<Esc>", "<cmd>nohlsearch<CR>")
vim.keymap.set("n", "<S-l>", ":bnext<CR>")
vim.keymap.set("n", "<S-h>", ":bprevious<CR>")
vim.keymap.set("n", "x", '"_x')
vim.keymap.set("v", "J", ":m '>+1<CR>gv=gv")
vim.keymap.set("v", "K", ":m '<-2<CR>gv=gv")
vim.keymap.set("n", "J", "mzJ`z")
vim.keymap.set("n", "<C-d>", "<C-d>zz")
vim.keymap.set("n", "<C-u>", "<C-u>zz")
vim.keymap.set("n", "<C-H>", "<C-W>h")
vim.keymap.set("n", "<C-J>", "<C-W>j")
vim.keymap.set("n", "<C-K>", "<C-W>k")
vim.keymap.set("n", "<C-L>", "<C-W>l")
vim.keymap.set("n", "<leader>fe", vim.diagnostic.open_float, { desc = "Show diagnostic [E]rror messages" })
vim.keymap.set("n", "<leader>fn", function() vim.diagnostic.jump({ count = 1 }) end)
vim.keymap.set("n", "<leader>fp", function() vim.diagnostic.jump({ count = -1 }) end)
vim.keymap.set("n", "<leader>rn", vim.lsp.buf.rename, { desc = "[R]e[n]ame" })
vim.keymap.set("n", "<leader>ca", vim.lsp.buf.code_action, { desc = "[C]ode [A]ction" })
vim.keymap.set("n", "K", vim.lsp.buf.hover, { desc = "Hover Documentation" })

vim.keymap.set("n", "<leader>p", function()
    require("conform").format({ async = true, lsp_fallback = true })
end)

local harpoon = require("harpoon")
harpoon:setup({})
vim.keymap.set("n", "<leader>a", function()
    harpoon:list():add()
end)
vim.keymap.set("n", "<C-e>", function()
    harpoon.ui:toggle_quick_menu(harpoon:list())
end)
for i = 1, 5 do
    vim.keymap.set("n", "<leader>" .. i, function()
        harpoon:list():select(i)
    end)
end

vim.cmd('colorscheme base16-black-metal-gorgoroth')

vim.diagnostic.config({
    float = { border = "single" },
})
