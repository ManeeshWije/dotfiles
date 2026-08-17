vim.opt.grepprg = "rg --vimgrep --smart-case --hidden"
vim.opt.grepformat = "%f:%l:%c:%m"

vim.keymap.set("n", "<leader>sg", function()
	vim.ui.input({ prompt = "Grep: " }, function(pattern)
		if pattern and pattern ~= "" then
			vim.cmd.grep({ pattern, bang = true })
			vim.cmd.copen()
		end
	end)
end, { silent = true })
