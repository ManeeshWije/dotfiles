local cached_files

local function build_file_list()
	local root = vim.fs.root(0, ".git")

	if root then
		return vim.fn.systemlist({
			"git",
			"-C",
			root,
			"ls-files",
			"--cached",
			"--others",
			"--exclude-standard",
		})
	end

	return vim.fn.glob("**/*", true, true)
end

function _G.native_find(text, _)
	cached_files = cached_files or build_file_list()
	return vim.fn.matchfuzzy(cached_files, text)
end

vim.opt.findfunc = "v:lua.native_find"

vim.keymap.set("n", "<leader>ff", ":find ", { silent = false })
