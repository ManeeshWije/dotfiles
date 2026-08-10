-- local ignore_patterns = {
-- 	"node_modules",
-- 	"%.git",
-- 	"%.cache",
-- 	"dist",
-- 	"build",
-- 	"%.tmp",
-- 	"%.log",
-- 	"target",
-- }
--
-- function _G.native_find(text, _)
-- 	local files = vim.fn.glob("**/*", true, true)
-- 	local result = {}
-- 	for _, f in ipairs(files) do
-- 		if vim.fn.isdirectory(f) == 0 then
-- 			local skip = false
-- 			for _, pat in ipairs(ignore_patterns) do
-- 				if f:match(pat) then
-- 					skip = true
-- 					break
-- 				end
-- 			end
-- 			if not skip then
-- 				result[#result + 1] = f
-- 			end
-- 		end
-- 	end
-- 	return vim.fn.matchfuzzy(result, text)
-- end
-- vim.opt.findfunc = "v:lua.native_find"
--
-- vim.keymap.set("n", "<leader>ff", ":find ", { silent = false })
local ignore_patterns = {
	"node_modules",
	".git",
	".cache",
	"dist",
	"build",
	"target",
}

local cached_files

local function build_file_list()
	local files = vim.fn.glob("**/*", true, true)

	return vim.tbl_filter(function(f)
		-- Fast Lua-side filtering first
		for _, dir in ipairs(ignore_patterns) do
			if f:find(dir, 1, true) then
				return false
			end
		end

		return vim.fn.isdirectory(f) == 0
	end, files)
end

function _G.native_find(text, _)
	cached_files = cached_files or build_file_list()
	return vim.fn.matchfuzzy(cached_files, text)
end

vim.opt.findfunc = "v:lua.native_find"

vim.keymap.set("n", "<leader>ff", ":find ", { silent = false })

