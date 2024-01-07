local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
if not vim.loop.fs_stat(lazypath) then
    vim.fn.system({
        "git",
        "clone",
        "--filter=blob:none",
        "https://github.com/folke/lazy.nvim.git",
        "--branch=stable", -- latest stable release
        lazypath,
    })
end
vim.opt.rtp:prepend(lazypath)

vim.g.mapleader = ","

local plugins = {
    {
        "sainnhe/gruvbox-material",
        lazy = false,    -- make sure we load this during startup
        priority = 1000, -- make sure to load this before all the other start plugins
    },

    { 'VonHeikemen/lsp-zero.nvim',        branch = 'v3.x' },

    -- LSP Support
    { 'williamboman/mason.nvim' },
    { 'williamboman/mason-lspconfig.nvim' },
    { 'neovim/nvim-lspconfig' },

    -- Autocompletion
    { 'hrsh7th/nvim-cmp' },
    { 'hrsh7th/cmp-nvim-lsp' },
    { 'hrsh7th/cmp-buffer' },
    { 'hrsh7th/cmp-path' },
    { 'saadparwaiz1/cmp_luasnip' },
    { 'hrsh7th/cmp-nvim-lua' },
    { 'L3MON4D3/LuaSnip' },
    { 'rafamadriz/friendly-snippets' },

    {
        'nvim-telescope/telescope.nvim',
        tag = '0.1.4',
        dependencies = { 'nvim-lua/plenary.nvim' }
    },

    {
        "iamcco/markdown-preview.nvim",
        cmd = { "MarkdownPreviewToggle", "MarkdownPreview", "MarkdownPreviewStop" },
        build = "cd app && yarn install",
        init = function()
            vim.g.mkdp_filetypes = { "markdown" }
        end,
        ft = { "markdown" },
    },

    {
        "nvim-lualine/lualine.nvim",
        dependencies = { "nvim-tree/nvim-web-devicons", lazy = true }
    },

    {
        "nvim-tree/nvim-tree.lua",
        dependencies = {
            "nvim-tree/nvim-web-devicons"
        }
    },

    { "nvim-treesitter/nvim-treesitter",     build = ":TSUpdate" },
    { "turbio/bracey.vim",                   build = "npm install --prefix server" },
    { "lukas-reineke/indent-blankline.nvim", main = "ibl",                         opts = {} },
    "nvim-tree/nvim-web-devicons",

    "nvimtools/none-ls.nvim",

    "lewis6991/gitsigns.nvim",

    "cohama/lexima.vim",

    "numToStr/Comment.nvim",

    "christoomey/vim-tmux-navigator",

    {
        "folke/trouble.nvim",
        dependencies = { "nvim-tree/nvim-web-devicons" },
        opts = {},
    },

    {
        "ThePrimeagen/harpoon",
        branch = "harpoon2",
        dependencies = { "nvim-lua/plenary.nvim" }
    }
}

local opts = {}
require("lazy").setup(plugins, opts)
