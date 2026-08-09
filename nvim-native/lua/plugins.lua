vim.pack.add({
	{ src = "https://github.com/nvim-treesitter/nvim-treesitter", version = "main" },
	{ src = "https://github.com/nvim-treesitter/nvim-treesitter-context" },
	{ src = "https://github.com/neovim/nvim-lspconfig" },
})

local ensure_installed = {
	"bash",
	"css",
	"dockerfile",
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
}

local tree = require("nvim-treesitter")
tree.setup({})
tree.install(ensure_installed)

local grp = vim.api.nvim_create_augroup("TreeSitterConfig", { clear = true })
vim.api.nvim_create_autocmd("FileType", {
	group = grp,
	callback = function(event)
		if vim.list_contains(tree.get_installed(), vim.treesitter.language.get_lang(event.match)) then
			vim.treesitter.start(event.buf)
		end
	end,
})

require("treesitter-context").setup({
	enable = true,
})
