-- Only required if you have packer configured as `opt`
vim.cmd.packadd('packer.nvim')

return require('packer').startup(function(use)
    -- Packer can manage itself
    use 'wbthomason/packer.nvim'

    use {
        'nvim-telescope/telescope.nvim', tag = '0.1.0',
        -- or                            , branch = '0.1.x',
        requires = { { 'nvim-lua/plenary.nvim' } }
    }

    use({ "sainnhe/gruvbox-material", as = 'gruvbox-material' })

    use({ "nvim-treesitter/nvim-treesitter", run = ":TSUpdate" })

    use {
        'VonHeikemen/lsp-zero.nvim',
        branch = 'v1.x',
        requires = {
            -- LSP Support
            { 'neovim/nvim-lspconfig' },
            { 'williamboman/mason.nvim' },
            { 'williamboman/mason-lspconfig.nvim' },

            -- Autocompletion
            { 'hrsh7th/nvim-cmp' },
            { 'hrsh7th/cmp-buffer' },
            { 'hrsh7th/cmp-path' },
            { 'saadparwaiz1/cmp_luasnip' },
            { 'hrsh7th/cmp-nvim-lsp' },
            { 'hrsh7th/cmp-nvim-lua' },

            -- Snippets
            { 'L3MON4D3/LuaSnip' },
            { 'rafamadriz/friendly-snippets' },
        }
    }
	use("jose-elias-alvarez/null-ls.nvim")
    use("github/copilot.vim")
    use("lewis6991/gitsigns.nvim")
    use("lukas-reineke/indent-blankline.nvim")
    use("windwp/nvim-autopairs")
    use("numToStr/Comment.nvim")
    use({ "turbio/bracey.vim", run = "npm install --prefix server" })
    use({
        "iamcco/markdown-preview.nvim",
        run = function()
            vim.fn["mkdp#util#install"]()
        end,
    })
    vim.cmd([[let g:gruvbox_material_background = 'hard']])
    vim.cmd([[colorscheme gruvbox-material]])
end)
