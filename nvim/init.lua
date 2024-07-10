-- opts
vim.g.mapleader = ","
vim.g.maplocalleader = ","
vim.g.loaded_netrw = 1
vim.g.loaded_netrwPlugin = 1
vim.opt.guicursor = ""
vim.opt.number = true
vim.opt.relativenumber = true
vim.opt.mouse = "a"
vim.opt.showmode = false
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
    { "numToStr/Comment.nvim", opts = {} },

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

            local builtin = require("telescope.builtin")
            local action_state = require("telescope.actions.state")
            local actions = require("telescope.actions")

            local buffer_searcher
            buffer_searcher = function()
                builtin.buffers({
                    sort_mru = true,
                    ignore_current_buffer = false,
                    show_all_buffers = false,
                    attach_mappings = function(prompt_bufnr, map)
                        local refresh_buffer_searcher = function()
                            actions.close(prompt_bufnr)
                            vim.schedule(buffer_searcher)
                        end
                        local delete_buf = function()
                            local selection = action_state.get_selected_entry()
                            vim.api.nvim_buf_delete(selection.bufnr, { force = true })
                            refresh_buffer_searcher()
                        end
                        local delete_multiple_buf = function()
                            local picker = action_state.get_current_picker(prompt_bufnr)
                            local selection = picker:get_multi_selection()
                            for _, entry in ipairs(selection) do
                                vim.api.nvim_buf_delete(entry.bufnr, { force = true })
                            end
                            refresh_buffer_searcher()
                        end
                        map("n", "dd", delete_buf)
                        map("n", "<C-d>", delete_multiple_buf)
                        map("i", "<C-d>", delete_multiple_buf)
                        return true
                    end,
                })
            end

            vim.keymap.set("n", "<leader>fh", builtin.help_tags)
            vim.keymap.set("n", "<leader>fk", builtin.keymaps)
            vim.keymap.set("n", "<leader>ff", builtin.find_files)
            vim.keymap.set("n", "<leader>fw", builtin.grep_string)
            vim.keymap.set("n", "<leader>fg", builtin.live_grep)
            vim.keymap.set("n", "<leader>fd", builtin.diagnostics)
            vim.keymap.set("n", "<leader>fb", buffer_searcher, {})
        end,
    },

    { -- LSP Configuration & Plugins
        "neovim/nvim-lspconfig",
        dependencies = {
            "williamboman/mason.nvim",
            "williamboman/mason-lspconfig.nvim",
            "WhoIsSethDaniel/mason-tool-installer.nvim",

            { "j-hui/fidget.nvim", opts = {} },
        },
        config = function()
            vim.api.nvim_create_autocmd("LspAttach", {
                group = vim.api.nvim_create_augroup("lsp-attach", { clear = true }),
                callback = function(event)
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

            local capabilities = vim.lsp.protocol.make_client_capabilities()
            capabilities = vim.tbl_deep_extend("force", capabilities, require("cmp_nvim_lsp").default_capabilities())

            local servers = {
                htmx = {},
                clangd = {},
                gopls = {},
                pyright = {},
                rust_analyzer = {},
                tsserver = {},
                bashls = {},
                cssls = {},
                dockerls = {},
                emmet_ls = {},
                eslint = {},
                html = {},
                jdtls = {},
                jsonls = {},
                ltex = {},
                phpactor = {},
                sqlls = {},
                tailwindcss = {},
                vimls = {},
                yamlls = {},
                lua_ls = {
                    settings = {
                        Lua = {
                            runtime = { version = "LuaJIT" },
                            workspace = {
                                checkThirdParty = false,
                                library = {
                                    "${3rd}/luv/library",
                                    unpack(vim.api.nvim_get_runtime_file("", true)),
                                },
                            },
                        },
                    },
                },
            }

            require("mason").setup()
            local ensure_installed = vim.tbl_keys(servers or {})
            vim.list_extend(ensure_installed, {
                "stylua",
            })

            require("mason-tool-installer").setup({ ensure_installed = ensure_installed })

            require("mason-lspconfig").setup({
                handlers = {
                    function(server_name)
                        local server = servers[server_name] or {}
                        require("lspconfig")[server_name].setup({
                            cmd = server.cmd,
                            settings = server.settings,
                            filetypes = server.filetypes,
                            capabilities = vim.tbl_deep_extend("force", {}, capabilities, server.capabilities or {}),
                        })
                    end,
                },
            })
        end,
    },

    { -- Autoformat
        "stevearc/conform.nvim",
        opts = {
            notify_on_error = false,
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
            },
        },
    },

    { -- Autocompletion
        "hrsh7th/nvim-cmp",
        event = "InsertEnter",
        dependencies = {
            {
                "L3MON4D3/LuaSnip",
                build = (function()
                    if vim.fn.has("win32") == 1 or vim.fn.executable("make") == 0 then
                        return
                    end
                    return "make install_jsregexp"
                end)(),
                dependencies = {
                    {
                        "rafamadriz/friendly-snippets",
                        config = function()
                            require("luasnip.loaders.from_vscode").lazy_load()
                        end,
                    },
                },
            },
            "saadparwaiz1/cmp_luasnip",
            "hrsh7th/cmp-nvim-lsp",
            "hrsh7th/cmp-path",
        },
        config = function()
            local cmp = require("cmp")
            local luasnip = require("luasnip")
            luasnip.config.setup({})
            luasnip.filetype_extend("handlebars", { "html" })

            cmp.setup({
                snippet = {
                    expand = function(args)
                        luasnip.lsp_expand(args.body)
                    end,
                },
                mapping = cmp.mapping.preset.insert({
                    ["<C-n>"] = cmp.mapping.select_next_item(),
                    ["<C-p>"] = cmp.mapping.select_prev_item(),
                    ["<C-j>"] = cmp.mapping.scroll_docs(4),
                    ["<C-k>"] = cmp.mapping.scroll_docs(-4),
                    ["<CR>"] = cmp.mapping.confirm({ select = false }),
                    ["<C-Space>"] = cmp.mapping.complete({}),
                    ["<C-l>"] = cmp.mapping(function()
                        if luasnip.expand_or_locally_jumpable() then
                            luasnip.expand_or_jump()
                        end
                    end, { "i", "s" }),
                    ["<C-h>"] = cmp.mapping(function()
                        if luasnip.locally_jumpable(-1) then
                            luasnip.jump(-1)
                        end
                    end, { "i", "s" }),
                }),
                sources = {
                    { name = "nvim_lsp" },
                    { name = "luasnip" },
                    { name = "path" },
                    { name = "vim-dadbod-completion" },
                },
                window = {
                    documentation = cmp.config.window.bordered(),
                    completion = {
                        winhighlight = "NormalFloat:NormalFloat,FloatBorder:NormalFloat",
                        border = "rounded",
                    },
                },
            })
        end,
    },

    {
        "f4z3r/gruvbox-material.nvim",
        name = "gruvbox-material",
        lazy = false,
        priority = 1000,
        opts = {},
    },

    { -- QOL improvements
        "echasnovski/mini.nvim",
        config = function()
            require("mini.ai").setup({ n_lines = 500 })
            require("mini.surround").setup()
            require("mini.statusline").setup()
            MiniStatusline.section_location = function()
                return "%2l:%-2v"
            end
        end,
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
        dependencies = { "hrsh7th/nvim-cmp" },
        config = function()
            require("nvim-autopairs").setup({})
            local cmp_autopairs = require("nvim-autopairs.completion.cmp")
            local cmp = require("cmp")
            cmp.event:on("confirm_done", cmp_autopairs.on_confirm_done())
        end,
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
})

-- Keymaps for certain plugins and settings
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

vim.keymap.set("n", "[d", vim.diagnostic.goto_prev, { desc = "Go to previous [D]iagnostic message" })
vim.keymap.set("n", "]d", vim.diagnostic.goto_next, { desc = "Go to next [D]iagnostic message" })
vim.keymap.set("n", "<leader>fe", vim.diagnostic.open_float, { desc = "Show diagnostic [E]rror messages" })
vim.keymap.set("n", "<leader>q", vim.diagnostic.setloclist, { desc = "Open diagnostic [Q]uickfix list" })

vim.keymap.set("n", "<C-H>", "<C-W>h")
vim.keymap.set("n", "<C-J>", "<C-W>j")
vim.keymap.set("n", "<C-K>", "<C-W>k")
vim.keymap.set("n", "<C-L>", "<C-W>l")

vim.keymap.set("n", "<leader>fu", "<cmd>Telescope undo<cr>")

vim.keymap.set("n", "<leader>p", function()
    require("conform").format()
end)

local harpoon = require("harpoon")
harpoon:setup({})
vim.keymap.set("n", "<leader>a", function()
    harpoon:list():add()
end)
vim.keymap.set("n", "<C-e>", function()
    harpoon.ui:toggle_quick_menu(harpoon:list())
end)
vim.keymap.set("n", "<leader>1", function()
    harpoon:list():select(1)
end)
vim.keymap.set("n", "<leader>2", function()
    harpoon:list():select(2)
end)
vim.keymap.set("n", "<leader>3", function()
    harpoon:list():select(3)
end)
vim.keymap.set("n", "<leader>4", function()
    harpoon:list():select(4)
end)
vim.keymap.set("n", "<leader>5", function()
    harpoon:list():select(5)
end)

require("gruvbox-material").setup({
    italics = true,
    contrast = "hard",
    comments = {
        italics = true,
    },
    background = {
        transparent = true,
    },
    float = {
        force_background = false,
        background_color = nil,
    },
    signs = {
        highlight = false,
    },
    customize = nil,
})

require("ibl").setup()
