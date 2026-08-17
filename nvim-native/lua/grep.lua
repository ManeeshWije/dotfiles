vim.opt.grepprg = "rg --vimgrep --smart-case --hidden"
vim.opt.grepformat = "%f:%l:%c:%m"

local function grep_complete(arglead, cmdline, _)
	local pattern = cmdline:match("^Grep%s+(.*)$") or arglead

	if pattern == "" then
		return {}
	end

	local results = vim.fn.systemlist({
		"rg",
		"--no-heading",
		"--color=never",
		"--smart-case",
		"--hidden",
		"--glob",
		"!.git",
		pattern,
	})

	return vim.list_slice(results, 1, 50)
end

vim.api.nvim_create_user_command("Grep", function(opts)
	vim.cmd("silent grep! " .. vim.fn.shellescape(opts.args))
	vim.cmd("copen")
end, {
	nargs = "+",
	complete = grep_complete,
})

vim.keymap.set("n", "<leader>sg", ":Grep ", { silent = false })
