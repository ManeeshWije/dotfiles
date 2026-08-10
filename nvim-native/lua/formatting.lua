local M = {}

-- filetype -> shell command
-- `%` gets replaced with the current buffer path.
M.formatters = {
	lua = "stylua -",
	javascript = "oxfmt --stdin-filepath %",
	javascriptreact = "oxfmt --stdin-filepath %",
	typescript = "oxfmt --stdin-filepath %",
	typescriptreact = "oxfmt --stdin-filepath %",
	rust = "rustfmt",
	sql = "sql-formatter",
	nix = "alejandra --quiet",
}

function M.format(bufnr)
	bufnr = bufnr or vim.api.nvim_get_current_buf()

	local ft = vim.bo[bufnr].filetype
	local cmd = M.formatters[ft]

	if cmd then
		local bufname = vim.api.nvim_buf_get_name(bufnr)

		-- Replace % with shell-escaped buffer path.
		local resolved = cmd:gsub("%%", vim.fn.shellescape(bufname))

		local lines = vim.api.nvim_buf_get_lines(bufnr, 0, -1, false)
		local input = table.concat(lines, "\n")

		local output = vim.fn.system(resolved, input)

		if vim.v.shell_error ~= 0 then
			vim.notify("Formatter failed:\n" .. output, vim.log.levels.ERROR)
			return
		end

		local formatted = vim.split(output, "\n", {
			plain = true,
		})

		if formatted[#formatted] == "" then
			table.remove(formatted)
		end

		vim.api.nvim_buf_set_lines(bufnr, 0, -1, false, formatted)

		return
	end

	-- Fall back to LSP formatting.
	for _, client in ipairs(vim.lsp.get_clients({ bufnr = bufnr })) do
		if client:supports_method("textDocument/formatting") then
			vim.lsp.buf.format({
				bufnr = bufnr,
				async = false,
			})
			return
		end
	end

	vim.notify("No formatter configured for " .. ft, vim.log.levels.WARN)
end

vim.keymap.set("n", "<leader>c", function()
	M.format()
end, {
	desc = "Format buffer",
})

return M
