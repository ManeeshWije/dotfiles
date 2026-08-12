vim.g.tsc_makeprg = "npx tsc"
--
local compiler_configs = {
	typescript = {
		patterns = { "typescript", "typescriptreact" },
		compiler = "tsc",
	},
}

for _, config in pairs(compiler_configs) do
	vim.api.nvim_create_autocmd("FileType", {
		pattern = config.patterns,
		callback = function()
			vim.cmd("compiler " .. config.compiler)
		end,
		desc = "Set up compiler for " .. table.concat(config.patterns, ", "),
	})
end

-- open qflist after make to go through errors
vim.api.nvim_create_autocmd("QuickFixCmdPost", {
	pattern = "make",
	callback = function()
		local qf = vim.fn.getqflist()
		for _, item in ipairs(qf) do
			if item.valid == 1 then
				vim.cmd("copen")
				return
			end
		end
	end,
})
