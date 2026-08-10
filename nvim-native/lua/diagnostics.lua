vim.keymap.set("n", "<leader>sd", function()
	vim.diagnostic.setqflist()
	vim.cmd("copen")
end, { silent = true })
