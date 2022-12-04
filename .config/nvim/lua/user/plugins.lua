local fn = vim.fn

-- Automatically install packer
local install_path = fn.stdpath("data") .. "/site/pack/packer/start/packer.nvim"
if fn.empty(fn.glob(install_path)) > 0 then
	PACKER_BOOTSTRAP = fn.system({
		"git",
		"clone",
		"--depth",
		"1",
		"https://github.com/wbthomason/packer.nvim",
		install_path,
	})
	print("Installing packer close and reopen Neovim...")
	vim.cmd([[packadd packer.nvim]])
end
-- Autocommand that reloads neovim whenever you save the plugins.lua file
vim.cmd([[
  augroup packer_user_config
    autocmd!
    autocmd BufWritePost plugins.lua source <afile> | PackerSync
  augroup end
]])

-- Use a protected call so we don't error out on first use
local status_ok, packer = pcall(require, "packer")
if not status_ok then
	return
end

-- Have packer use a popup window
packer.init({
	display = {
		open_fn = function()
			return require("packer.util").float({ border = "rounded" })
		end,
	},
})

-- Install your plugins here
return packer.startup(function(use)
	-- Utils
	use("wbthomason/packer.nvim") -- Have packer manage itself
	use("nvim-lua/popup.nvim") -- An implementation of the Popup API from vim in Neovim
	use("nvim-lua/plenary.nvim") -- Useful lua functions used by lots of plugins
	use("windwp/nvim-autopairs") -- auto brackets
	use("numToStr/Comment.nvim") -- Easily comment stuff
	use("JoosepAlviste/nvim-ts-context-commentstring") -- content commenting
	use({ "turbio/bracey.vim", run = "npm install --prefix server" }) -- live server

	-- interface
	use("kyazdani42/nvim-web-devicons") -- file icons
	use("kyazdani42/nvim-tree.lua") -- file tree
	use("nvim-lualine/lualine.nvim") -- status line
	use("ap/vim-css-color") -- css colours
	use("lewis6991/gitsigns.nvim") -- git sign column
  use "lukas-reineke/indent-blankline.nvim" -- show indents

	-- colorscheme
	use("shaunsingh/nord.nvim")

	-- cmp plugins
	use("hrsh7th/nvim-cmp") -- The completion plugin
	use("hrsh7th/cmp-buffer") -- buffer completions
	use("hrsh7th/cmp-path") -- path completions
	use("saadparwaiz1/cmp_luasnip") -- snippet completions
	use("hrsh7th/cmp-nvim-lsp")
	use("hrsh7th/cmp-nvim-lua")

	-- snippets
	use("L3MON4D3/LuaSnip") --snippet engine
	use("rafamadriz/friendly-snippets") -- a bunch of snippets to use

	-- LSP
	use("neovim/nvim-lspconfig") -- enable LSP
	use("williamboman/mason.nvim") -- simple to use language server installer
	use("williamboman/mason-lspconfig.nvim") -- simple to use language server installer
	use("jose-elias-alvarez/null-ls.nvim") -- Diagnostics and formatting

	-- Telescope
	use("nvim-telescope/telescope.nvim") -- fuzzy find

	-- Treesitter
	use({
		"nvim-treesitter/nvim-treesitter", -- syntax highlight
		run = ":TSUpdate",
	})
	use("p00f/nvim-ts-rainbow") -- bracket pair colorizer

	-- Debugging
	use("mfussenegger/nvim-dap") -- debug adapter
	use("rcarriga/nvim-dap-ui") -- ui for debugging
	use("mfussenegger/nvim-dap-python") -- python debug
	use("ravenxrz/DAPInstall.nvim") -- install adapters
  use 'mfussenegger/nvim-jdtls' -- java stuff

	-- Automatically set up your configuration after cloning packer.nvim
	-- Put this at the end after all plugins
	if PACKER_BOOTSTRAP then
		require("packer").sync()
	end
end)
