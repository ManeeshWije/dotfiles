vim.opt.grepformat = "%f:%l:%c:%m"

local function grep_complete(arglead, _, _)
	if arglead == "" then
		return {}
	end

	local lines = vim.fn.systemlist({
		"rg",
		"--no-heading",
		"--no-filename",
		"--color=never",
		"--smart-case",
		"--hidden",
		"--glob",
		"!.git",
		"--",
		arglead,
	})

	local words = {}

	for _, line in ipairs(lines) do
		for word in line:gmatch("[%w_%.%-]+") do
			if word:lower():find(arglead:lower(), 1, true) then
				words[word] = true
			end
		end
	end

	return vim.tbl_keys(words)
end

vim.api.nvim_create_user_command("Grep", function(opts)
	vim.cmd("silent grep! " .. vim.fn.shellescape(opts.args))
	vim.cmd("copen")
end, {
	nargs = "+",
	complete = grep_complete,
})

vim.keymap.set("n", "<leader>sg", ":Grep ", { silent = false })
