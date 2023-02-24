local servers = {
	"lua_ls",
	"pyright",
	"jsonls",
	"tsserver",
	"eslint",
	"emmet_ls",
	"html",
	"vimls",
	"bashls",
	"clangd",
	"cssls",
	"graphql",
	"rust_analyzer",
	"dockerls",
	"sqlls",
	"tailwindcss",
	"jdtls",
	"als",
	"fortls",
	"ltex",
}

local settings = {
	ui = {
		border = "none",
		icons = {
			package_installed = "◍",
			package_pending = "◍",
			package_uninstalled = "◍",
		},
	},
	log_level = vim.log.levels.INFO,
	max_concurrent_installers = 4,
}

require("mason").setup(settings)
require("mason-lspconfig").setup({
	ensure_installed = servers,
	automatic_installation = true,
})

local lspconfig_status_ok, lspconfig = pcall(require, "lspconfig")
if not lspconfig_status_ok then
	return
end

local opts = {}

for _, server in pairs(servers) do
	opts = {
		on_attach = require("maneesh.lsp.handlers").on_attach,
		capabilities = require("maneesh.lsp.handlers").capabilities,
	}

	server = vim.split(server, "@")[1]

	lspconfig[server].setup(opts)
end
