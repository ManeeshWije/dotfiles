-- Options
vim.g.loaded_netrw = 1
vim.g.loaded_netrwPlugin = 1
vim.o.number = true
vim.o.relativenumber = true
vim.o.signcolumn = "yes"
vim.o.termguicolors = true
vim.o.wrap = false
vim.o.swapfile = false
vim.g.mapleader = ","
vim.o.winborder = "single"
vim.o.clipboard = "unnamedplus"
vim.o.guicursor = ""
vim.o.ignorecase = true
vim.o.smartcase = true
vim.o.updatetime = 250
vim.o.timeoutlen = 300
vim.o.scrolloff = 10
vim.o.sidescrolloff = 10
vim.o.hlsearch = true
vim.o.tabstop = 4
vim.o.softtabstop = 4
vim.o.shiftwidth = 4
vim.o.expandtab = true
vim.o.smartindent = true
vim.o.previewheight = 25
vim.opt.fillchars = { fold = " " }
vim.o.foldmethod = "indent"
vim.o.foldenable = false
vim.o.foldlevel = 99
vim.o.list = false
vim.opt.listchars = { tab = '» ', trail = '·', nbsp = '␣' }
vim.g.markdown_folding = 1
vim.o.splitright = true
vim.o.splitbelow = true

-- Plugins
vim.pack.add({
    { src = "https://github.com/nvim-lua/plenary.nvim" },
    { src = "https://github.com/RRethy/base16-nvim" },
    { src = "https://github.com/nvim-treesitter/nvim-treesitter" },
    { src = "https://github.com/nvim-treesitter/nvim-treesitter-context" },
    { src = "https://github.com/ibhagwan/fzf-lua" },
    { src = "https://github.com/ManeeshWije/git_browse.nvim" },
    { src = "https://github.com/rolv-apneseth/tfm.nvim" },
    { src = "https://github.com/iamcco/markdown-preview.nvim" },
    { src = "https://github.com/stevearc/conform.nvim" },
    { src = "https://github.com/tpope/vim-dadbod" },
    { src = "https://github.com/kristijanhusak/vim-dadbod-ui" },
    { src = "https://github.com/kristijanhusak/vim-dadbod-completion" },
    { src = "https://github.com/f-person/auto-dark-mode.nvim" },
})
vim.cmd(":hi statusline guibg=NONE")
vim.cmd("set completeopt+=noselect")

-- Setup plugins
require "auto-dark-mode".setup({
    set_dark_mode = function()
        vim.cmd('colorscheme base16-black-metal-gorgoroth')
    end,
    set_light_mode = function()
        vim.cmd('colorscheme base16-ayu-light')
    end,
    update_interval = 3000,
    fallback = "dark"
})
require "fzf-lua".setup({
    keymap = {
        builtin = {
            ["<C-a>"] = "select-all+accept",
            ["<C-d>"] = "half-page-down",
            ["<C-u>"] = "half-page-up",
            ["<C-f>"] = "preview-page-down",
            ["<C-b>"] = "preview-page-up",
            ["<C-n>"] = "down",
            ["<C-p>"] = "up",
        },
        fzf = {
            ["ctrl-a"] = "select-all+accept",
            ["ctrl-d"] = "half-page-down",
            ["ctrl-u"] = "half-page-up",
            ["ctrl-f"] = "preview-page-down",
            ["ctrl-b"] = "preview-page-up",
            ["ctrl-n"] = "down",
            ["ctrl-p"] = "up",
        },
    }
})
require "nvim-treesitter.configs".setup({
    ensure_installed = {
        "bash",
        "c",
        "cpp",
        "css",
        "dockerfile",
        "go",
        "html",
        "javascript",
        "json",
        "lua",
        "markdown",
        "python",
        "rust",
        "sql",
        "typescript",
        "vim",
        "yaml",
        "java",
        "php",
    },
    auto_install = true,
    sync_install = false,
    highlight = { enable = true },
    indent = { enable = true }
})
require "treesitter-context".setup({
    enable = true
})
require "conform".setup({
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
})

vim.lsp.enable({
    "gopls",
    "lua_ls",
    "ts_ls",
    "pyright",
    "clangd",
    "html",
    "cssls",
    "jsonls",
    "bashls",
    "dockerls",
    "yamlls",
    "rust_analyzer",
    "eslint",
    "tailwindcss",
    "jdtls",
    "emmet_ls",
})

-- Keymaps
local fzf = require("fzf-lua")
vim.keymap.set("n", "<leader>e", "", {
    noremap = true,
    callback = require("tfm").open,
})
vim.keymap.set("n", "<leader>ff", fzf.files, { noremap = true, silent = true })                -- File find
vim.keymap.set("n", "<leader>fg", fzf.git_files, { noremap = true, silent = true })            -- Git file find
vim.keymap.set("n", "<leader>fb", fzf.buffers, { noremap = true, silent = true })              -- Find buffer
vim.keymap.set("n", "<leader>sg", fzf.live_grep, { noremap = true, silent = true })            -- Grep string

vim.keymap.set("n", "<leader>gs", fzf.git_status, { noremap = true, silent = true })           -- git status
vim.keymap.set("n", "<leader>gd", fzf.git_diff, { noremap = true, silent = true })             -- git diff {ref}
vim.keymap.set("n", "<leader>gc", fzf.git_commits, { noremap = true, silent = true })          -- git commits (project)
vim.keymap.set("n", "<leader>gb", fzf.git_bcommits, { noremap = true, silent = true })         -- git commits (buffer)
vim.keymap.set("n", "<leader>gB", fzf.git_blame, { noremap = true, silent = true })            -- git blame (buffer)
vim.keymap.set("n", "<leader>gr", fzf.git_branches, { noremap = true, silent = true })         -- git branches
vim.keymap.set("n", "<leader>gt", fzf.git_tags, { noremap = true, silent = true })             -- git tags
vim.keymap.set("n", "<leader>gS", fzf.git_stash, { noremap = true, silent = true })            -- git stash

vim.keymap.set("n", "<leader>sm", fzf.spellcheck, { noremap = true, silent = true })           -- Misspelled words
vim.keymap.set("n", "<leader>sp", fzf.spell_suggest, { noremap = true, silent = true })        -- Suggestions for word under cursor

vim.keymap.set("n", "<leader>fh", fzf.help_tags, { noremap = true, silent = true })            -- Help tags
vim.keymap.set("n", "<leader>df", fzf.diagnostics_document, { noremap = true, silent = true }) -- Document Diagnostics

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
vim.keymap.set("n", "<C-W>\\", ":vnew<CR>")
vim.keymap.set("n", "<C-W>-", ":new<CR>")
vim.keymap.set("n", "q", "<cmd>cclose<cr>", { desc = "Close quickfix list" })
vim.keymap.set("n", "<leader>q", ":bd<CR>", { desc = "Close current buffer" })
vim.keymap.set("n", "<leader>p", function() require("conform").format({ async = true, lsp_fallback = true }) end,
    { desc = "Format Document" })
vim.keymap.set("i", "<C-space>", function()
    if vim.bo.omnifunc ~= "" then
        -- If omnifunc is set (like in SQL files), use omni-completion
        return "<C-x><C-o>"
    else
        -- Otherwise use LSP completion
        return vim.lsp.completion.get()
    end
end, { expr = true, desc = "Smart completion" })
vim.keymap.set({ "n", "t" }, "<leader>tt", function()
    vim.cmd.term()
    vim.cmd("startinsert")
end)
vim.keymap.set("n", "<leader>st", function()
    vim.cmd.vnew()
    vim.cmd.term()
    vim.cmd.wincmd("J")
    vim.api.nvim_win_set_height(0, 10)
    vim.cmd("startinsert")
end)
vim.keymap.set("n", "<leader>vt", function()
    vim.cmd.vnew()
    vim.cmd.term()
    vim.cmd.wincmd("L")
    vim.cmd("startinsert")
end)
vim.keymap.set("t", "<Esc><Esc>", "<C-\\><C-n>")
vim.keymap.set("t", "<C-H>", "<C-\\><C-N><C-w>h")
vim.keymap.set("t", "<C-J>", "<C-\\><C-N><C-w>j")
vim.keymap.set("t", "<C-K>", "<C-\\><C-N><C-w>k")
vim.keymap.set("t", "<C-L>", "<C-\\><C-N><C-w>l")

-- Autocommands
-- remember last cursor position
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

-- remember folds
vim.api.nvim_create_augroup("remember_folds", { clear = true })
vim.api.nvim_create_autocmd("BufWinLeave", {
    group = "remember_folds",
    pattern = "?*",
    command = "mkview 1",
})
vim.api.nvim_create_autocmd("BufWinEnter", {
    group = "remember_folds",
    pattern = "?*",
    command = "silent! loadview 1",
})

-- enable autocompletion for LSP
vim.api.nvim_create_autocmd('LspAttach', {
    callback = function(ev)
        local client = vim.lsp.get_client_by_id(ev.data.client_id)
        if client:supports_method('textDocument/completion') then
            vim.lsp.completion.enable(true, client.id, ev.buf, { autotrigger = true })
        end
    end,
})

-- vim dadbod config
vim.g.db_ui_use_omni = 1
vim.g.db_ui_connections_json = vim.fn.expand("~/.local/share/db_ui/connections.json")
vim.g.db_completion_enabled = 1
vim.g.omni_sql_no_default_maps = 1
vim.api.nvim_create_autocmd("FileType", {
    pattern = { "sql", "mysql", "plsql" },
    callback = function()
        vim.bo.omnifunc = "vim_dadbod_completion#omni"
        vim.bo.completefunc = "vim_dadbod_completion#omni"
        vim.bo.commentstring = "-- %s"
    end,
})
vim.api.nvim_create_autocmd("FileType", {
    pattern = "dbui",
    callback = function()
        vim.bo.buflisted = false
    end,
})
