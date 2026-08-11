vim.keymap.set({ "n", "x" }, "<leader>y", '"+y')
vim.keymap.set({ "n", "x" }, "<leader>yy", '"+yy')
vim.keymap.set({ "n", "x" }, "<leader>p", '"+p')
vim.keymap.set("i", "jk", "<Esc>")
vim.keymap.set("n", "<Esc>", "<cmd>nohlsearch<CR>")
vim.keymap.set("n", "<S-l>", ":bnext<CR>")
vim.keymap.set("n", "<S-h>", ":bprevious<CR>")
vim.keymap.set({ "n", "x" }, "x", '"_x')
vim.keymap.set("v", "J", ":m '>+1<CR>gv=gv")
vim.keymap.set("v", "K", ":m '<-2<CR>gv=gv")
vim.keymap.set("n", "J", "mzJ`z")
vim.keymap.set("n", "<C-d>", "<C-d>zz")
vim.keymap.set("n", "<C-u>", "<C-u>zz")
vim.keymap.set("n", "<C-H>", "<C-W>h")
vim.keymap.set("n", "<C-J>", "<C-W>j")
vim.keymap.set("n", "<C-K>", "<C-W>k")
vim.keymap.set("n", "<C-L>", "<C-W>l")
vim.keymap.set("n", "<leader>q", "<cmd>cclose<cr>", { desc = "Close quickfix list" })
vim.keymap.set("c", "<C-d>", "<PageDown>", { remap = false })
vim.keymap.set("c", "<C-u>", "<PageUp>", { remap = false })
vim.keymap.set("n", "<leader>fb", ":buffer ", { silent = false })
-- close buffer in wildmenu
vim.keymap.set("c", "<C-x>", function()
	if vim.fn.getcmdtype() ~= ":" then
		return "<C-x>"
	end

	local cmdline = vim.fn.getcmdline()
	local name = cmdline:match("^buffer%s+(.+)$")

	if not name or name == "" then
		return "<C-x>"
	end

	vim.schedule(function()
		local bufnr = vim.fn.bufnr(name)

		if bufnr ~= -1 then
			vim.api.nvim_buf_delete(bufnr, { force = false })
		end
	end)

	return "<C-c>"
end, { expr = true })
-- manual autocomplete
vim.keymap.set("i", "<C-space>", function()
	if vim.bo.omnifunc ~= "" then
		-- If omnifunc is set (like in SQL files), use omni-completion
		return "<C-x><C-o>"
	else
		-- Otherwise use LSP completion
		return vim.lsp.completion.get()
	end
end, { expr = true, desc = "Smart completion" })
-- Terminal window navigation
vim.keymap.set("t", "<C-h>", [[<C-\><C-n><C-w>h]], { silent = true })
vim.keymap.set("t", "<C-j>", [[<C-\><C-n><C-w>j]], { silent = true })
vim.keymap.set("t", "<C-k>", [[<C-\><C-n><C-w>k]], { silent = true })
vim.keymap.set("t", "<C-l>", [[<C-\><C-n><C-w>l]], { silent = true })
vim.keymap.set("t", "<Esc><Esc>", [[<C-\><C-n>]], { desc = "Terminal normal mode" })
vim.keymap.set("n", "<leader>t", ":term<CR>", { desc = "Open terminal as new buffer" })
vim.keymap.set("n", "<leader>tv", ":botright vsplit | term<CR>", { desc = "Open terminal vertically" })
vim.keymap.set("n", "<leader>th", ":botright split | term<CR>", { desc = "Open terminal horizontally" })
