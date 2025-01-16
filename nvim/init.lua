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
vim.filetype.add({
    extension = {
        hbs = "html",
    },
})

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
    { -- Adds git related signs to the gutter, as well as utilities for managing changes
        "lewis6991/gitsigns.nvim",
        opts = {
            signs = {
                add = { text = "+" },
                change = { text = "~" },
                delete = { text = "_" },
                topdelete = { text = "‾" },
                changedelete = { text = "~" },
            },
            current_line_blame = true, -- Toggle with `:Gitsigns toggle_current_line_blame`
            current_line_blame_opts = {
                virt_text = true,
                virt_text_pos = "eol", -- 'eol' | 'overlay' | 'right_align'
                delay = 1000,
                ignore_whitespace = false,
            },
            current_line_blame_formatter = "<author>, <author_time:%R> - <summary>",
        },
    },

    { -- fuzzy find
        "nvim-telescope/telescope.nvim",
        event = "VeryLazy",
        branch = "0.1.x",
        dependencies = {
            "nvim-lua/plenary.nvim",
            {
                "nvim-telescope/telescope-fzf-native.nvim",
                build = "make",
                cond = function()
                    return vim.fn.executable("make") == 1
                end,
            },
            { "nvim-telescope/telescope-ui-select.nvim" },
            { "nvim-tree/nvim-web-devicons" },
            { "debugloop/telescope-undo.nvim" },
        },
        config = function()
            require("telescope").setup({
                defaults = {
                    layout_strategy = "horizontal",
                    layout_config = { width = 0.99 },
                },
                extensions = {
                    ["ui-select"] = {
                        require("telescope.themes").get_dropdown(),
                    },
                    undo = {},
                },
                require("telescope").load_extension("undo"),
            })

            pcall(require("telescope").load_extension, "fzf")
            pcall(require("telescope").load_extension, "ui-select")
        end,
    },

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
                templ = {},
                htmx = {},
                clangd = {},
                gopls = {},
                pyright = {},
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
                omnisharp = {},
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
                    local map = function(keys, func, desc)
                        vim.keymap.set("n", keys, func, { buffer = event.buf, desc = "LSP: " .. desc })
                    end

                    map("gd", require("telescope.builtin").lsp_definitions, "[G]oto [D]efinition")
                    map("gr", require("telescope.builtin").lsp_references, "[G]oto [R]eferences")
                    map("gI", require("telescope.builtin").lsp_implementations, "[G]oto [I]mplementation")
                    map("<leader>D", require("telescope.builtin").lsp_type_definitions, "Type [D]efinition")
                    map("<leader>ds", require("telescope.builtin").lsp_document_symbols, "[D]ocument [S]ymbols")
                    map("<leader>ws", require("telescope.builtin").lsp_dynamic_workspace_symbols, "[W]orkspace [S]ymbols")
                    map("<leader>rn", vim.lsp.buf.rename, "[R]e[n]ame")
                    map("<leader>ca", vim.lsp.buf.code_action, "[C]ode [A]ction")
                    map("K", vim.lsp.buf.hover, "Hover Documentation")
                    map("gD", vim.lsp.buf.declaration, "[G]oto [D]eclaration")

                    -- OmniSharp-specific keybindings
                    if client.name == "omnisharp" then
                        local omnisharp_ext = require("omnisharp_extended")
                        map("gd", omnisharp_ext.telescope_lsp_definition, "[G]oto [D]efinition (OmniSharp)")
                        map("gr", omnisharp_ext.telescope_lsp_references, "[G]oto [R]eferences (OmniSharp)")
                        map("gI", omnisharp_ext.telescope_lsp_implementation, "[G]oto [I]mplementation (OmniSharp)")
                        map("<leader>D", omnisharp_ext.telescope_lsp_type_definition, "Type [D]efinition (OmniSharp)")
                    end

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
                sql = { "sql-formatter" },
                html = { "prettier" },
                handlebars = { "prettier" },
            },
        },
    },

    { -- Autocompletion
        "saghen/blink.cmp",
        dependencies = {
            "rafamadriz/friendly-snippets",
            { "L3MON4D3/LuaSnip", version = "v2.*" },
        },
        version = "*",
        opts = {
            snippets = {
                preset = "luasnip",
                expand = function(snippet)
                    require("luasnip").lsp_expand(snippet)
                end,
                active = function(filter)
                    if filter and filter.direction then
                        return require("luasnip").jumpable(filter.direction)
                    end
                    return require("luasnip").in_snippet()
                end,
                jump = function(direction)
                    require("luasnip").jump(direction)
                end,
            },
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
                    auto_show_delay_ms = 0,
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
            sources = {
                default = { "lsp", "path", "snippets", "buffer", "dadbod" },
                cmdline = {},
                providers = {
                    lsp = {
                        name = "lsp",
                        enabled = true,
                        module = "blink.cmp.sources.lsp",
                        fallbacks = { "snippets", "buffer" },
                        score_offset = 90,
                    },
                    path = {
                        name = "path",
                        module = "blink.cmp.sources.path",
                        score_offset = 3,
                        fallbacks = { "snippets", "luasnip", "buffer" },
                        opts = {
                            trailing_slash = false,
                            label_trailing_slash = true,
                            get_cwd = function(context)
                                return vim.fn.expand(("#%d:p:h"):format(context.bufnr))
                            end,
                            show_hidden_files_by_default = true,
                        },
                    },
                    buffer = {
                        name = "buffer",
                        module = "blink.cmp.sources.buffer",
                        min_keyword_length = 2,
                    },
                    snippets = {
                        name = "snippets",
                        enabled = true,
                        module = "blink.cmp.sources.snippets",
                        score_offset = 80,
                    },
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
        "f4z3r/gruvbox-material.nvim",
        name = "gruvbox-material",
        lazy = false,
        priority = 1000,
        opts = {},
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

    { -- Indentation
        "lukas-reineke/indent-blankline.nvim",
        main = "ibl",
        opts = {
            indent = {
                char = "▏",
            },
        },
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

    {
        "Hoffs/omnisharp-extended-lsp.nvim",
    },
})

-- Keymaps for certain plugins and settings
local builtin = require("telescope.builtin")
vim.keymap.set("n", "<leader>fh", builtin.help_tags)
vim.keymap.set("n", "<leader>fk", builtin.keymaps)
vim.keymap.set("n", "<leader>ff", builtin.find_files)
vim.keymap.set("n", "<leader>fw", builtin.grep_string)
vim.keymap.set("n", "<leader>fg", builtin.live_grep)
vim.keymap.set("n", "<leader>fd", builtin.diagnostics)
vim.keymap.set("n", "<leader>fb", builtin.buffers)
vim.keymap.set("n", "<leader>fu", "<cmd>Telescope undo<cr>")

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

vim.keymap.set("n", "[d", function()
    vim.diagnostic.jump({ count = -1, float = true })
end, { desc = "Go to previous [D]iagnostic message" })

vim.keymap.set("n", "]d", function()
    vim.diagnostic.jump({ count = 1, float = true })
end, { desc = "Go to next [D]iagnostic message" })
vim.keymap.set("n", "<leader>fe", vim.diagnostic.open_float, { desc = "Show diagnostic [E]rror messages" })

vim.keymap.set("n", "<C-H>", "<C-W>h")
vim.keymap.set("n", "<C-J>", "<C-W>j")
vim.keymap.set("n", "<C-K>", "<C-W>k")
vim.keymap.set("n", "<C-L>", "<C-W>l")

vim.keymap.set("n", "<leader>p", function()
    require("conform").format({ async = true, lsp_fallback = true })
end)

vim.keymap.set("n", "<leader>e", function()
    require("tfm").open()
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

require("gruvbox-material").setup({
    contrast = "hard",
    background = {
        transparent = true,
    },
    signs = {
        highlight = false,
    },
})
require("ibl").setup()

require("lspconfig").omnisharp.setup({
    cmd = { "dotnet", "/home/maneesh/Downloads/omnisharp-linux-x64-net6.0/OmniSharp.dll" },
})
