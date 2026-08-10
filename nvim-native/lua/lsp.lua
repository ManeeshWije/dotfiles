-- lsp
vim.lsp.enable({
	"lua_ls",
	"tsgo",
	"oxlint",
	"oxfmt",
	"rust_analyzer",
	"docker_language_server",
	"bashls",
	"cssls",
	"html",
	"jsonls",
	"nixd",
	"pyright",
	"stylua",
	"tailwindcss",
	"yamlls",
})

vim.g.tsc_makeprg = "yarn run tsc"

local all_levels = {
	vim.diagnostic.severity.ERROR,
	vim.diagnostic.severity.WARN,
	vim.diagnostic.severity.HINT,
	vim.diagnostic.severity.INFO,
}

vim.diagnostic.config({
	severity_sort = true,
	virtual_lines = false,
	signs = {
		severity = all_levels,
	},
	underline = {
		severity = all_levels,
	},
	virtual_text = {
		severity = all_levels,
	},
	float = {
		severity = all_levels,
	},
})

vim.api.nvim_create_autocmd("LspAttach", {
	callback = function(ev)
		local client = vim.lsp.get_client_by_id(ev.data.client_id)
		if client ~= nil and client:supports_method("textDocument/completion") then
			vim.lsp.completion.enable(true, client.id, ev.buf, { autotrigger = true })
		end
	end,
})

vim.cmd("set completeopt+=noselect")
