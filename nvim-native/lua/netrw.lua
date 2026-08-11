vim.g.netrw_winsize = 25

vim.keymap.set("n", "<leader>e", function()
    local current_buf = vim.api.nvim_get_current_buf()

    -- If this window is already netrw, go back
    if vim.bo[current_buf].filetype == "netrw" then
        vim.cmd("buffer #")
        return
    end

    local dir = vim.fn.expand("%:p:h")

    if dir == "" then
        dir = vim.fn.getcwd()
    end

    vim.cmd("edit " .. vim.fn.fnameescape(dir))
end, {
    silent = true,
    desc = "Toggle netrw in current window",
})

-- netrw's built-in `%` opens new files in the netrw window instead of
-- respecting `netrw_browse_split`. Override it to open in the previous window.
vim.api.nvim_create_autocmd("FileType", {
	pattern = "netrw",
	callback = function()
		vim.keymap.set("n", "%", function()
			local fname = vim.fn.input("Enter filename: ")
			if fname == "" then
				return
			end

			local dir = vim.b.netrw_curdir or vim.fn.getcwd()
			local path = dir .. "/" .. fname

			if vim.fn.filereadable(path) == 1 or vim.fn.isdirectory(path) == 1 then
				vim.notify("Already exists: " .. fname, vim.log.levels.WARN)
				return
			end

			if fname:match("/$") then
				vim.fn.mkdir(path, "p")
				vim.cmd("edit")
			else
				local f = io.open(path, "w")
				if not f then
					vim.notify("Failed to create: " .. fname, vim.log.levels.ERROR)
					return
				end
				f:close()

				local escaped = vim.fn.fnameescape(path)
				if vim.fn.winnr("#") == 0 then
					vim.cmd("edit " .. escaped)
				else
					vim.cmd("wincmd p")
					vim.cmd("edit " .. escaped)
				end
			end
		end, { buffer = true, silent = true, noremap = true, desc = "Create file in previous window" })
	end,
})
