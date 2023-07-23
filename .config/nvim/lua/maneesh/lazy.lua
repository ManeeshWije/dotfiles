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
        lazy = false,    -- make sure we load this during startup if it is your main colorscheme
        priority = 1000, -- make sure to load this before all the other start plugins
        config = function()
            -- load the colorscheme here
            vim.cmd([[let g:gruvbox_material_background = "hard"]])
            vim.cmd([[let g:gruvbox_material_diagnostic_virtual_text = "colored"]])
            vim.cmd([[colorscheme gruvbox-material]])
        end,

    },

    {
        "VonHeikemen/lsp-zero.nvim",
        branch = 'v1.x',
        dependencies = {
            -- LSP Support
            { "neovim/nvim-lspconfig" },
            { "williamboman/mason.nvim" },
            { "williamboman/mason-lspconfig.nvim" },

            -- Autocompletion
            { "hrsh7th/nvim-cmp" },
            { "hrsh7th/cmp-buffer" },
            { "hrsh7th/cmp-path" },
            { "saadparwaiz1/cmp_luasnip" },
            { "hrsh7th/cmp-nvim-lsp" },
            { "hrsh7th/cmp-nvim-lua" },

            --Snippets
            { "L3MON4D3/LuaSnip" },
            { "rafamadriz/friendly-snippets" },
        }
    },

    {
        "nvim-telescope/telescope.nvim",
        version = "0.1.0",
        dependencies = { { "nvim-lua/plenary.nvim" } }
    },

    {
        "iamcco/markdown-preview.nvim",
        build = function()
            vim.fn["mkdp#util#install"]()
        end,
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

    { "nvim-treesitter/nvim-treesitter", build = ":TSUpdate" },

    { "turbio/bracey.vim",               build = "npm install --prefix server" },

    "nvim-tree/nvim-web-devicons",

    "jose-elias-alvarez/null-ls.nvim",

    "github/copilot.vim",

    "lewis6991/gitsigns.nvim",

    "lukas-reineke/indent-blankline.nvim",

    "windwp/nvim-autopairs",

    "numToStr/Comment.nvim",
}

local opts = {}

require("lazy").setup(plugins, opts)
