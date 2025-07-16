local fzf = require("fzf-lua")

vim.keymap.set("n", "<leader>ff", fzf.files, { noremap = true, silent = true })         -- File find
vim.keymap.set("n", "<leader>fg", fzf.git_files, { noremap = true, silent = true })     -- Git file find
vim.keymap.set("n", "<leader>fb", fzf.buffers, { noremap = true, silent = true })       -- Find buffer
vim.keymap.set("n", "<leader>sg", fzf.live_grep, { noremap = true, silent = true })     -- Grep string

vim.keymap.set("n", "<leader>gs", fzf.git_status, { noremap = true, silent = true })    -- git status
vim.keymap.set("n", "<leader>gd", fzf.git_diff, { noremap = true, silent = true })      -- git diff {ref}
vim.keymap.set("n", "<leader>gc", fzf.git_commits, { noremap = true, silent = true })   -- git commits (project)
vim.keymap.set("n", "<leader>gb", fzf.git_bcommits, { noremap = true, silent = true })  -- git commits (buffer)
vim.keymap.set("n", "<leader>gB", fzf.git_blame, { noremap = true, silent = true })     -- git blame (buffer)
vim.keymap.set("n", "<leader>gr", fzf.git_branches, { noremap = true, silent = true })  -- git branches
vim.keymap.set("n", "<leader>gt", fzf.git_tags, { noremap = true, silent = true })      -- git tags
vim.keymap.set("n", "<leader>gS", fzf.git_stash, { noremap = true, silent = true })     -- git stash

vim.keymap.set("n", "<leader>sm", fzf.spellcheck, { noremap = true, silent = true })    -- Misspelled words
vim.keymap.set("n", "<leader>sp", fzf.spell_suggest, { noremap = true, silent = true }) -- Suggestions for word under cursor

vim.keymap.set("i", "jk", "<Esc>")
vim.keymap.set("n", "<Esc>", "<cmd>nohlsearch<CR>")
vim.keymap.set("n", "<S-l>", ":bnext<CR>")
vim.keymap.set("n", "<S-h>", ":bprevious<CR>")
vim.keymap.set("n", "x", '"_x')
vim.keymap.set("v", "J", ":m '>+1<CR>gv=gv")
vim.keymap.set("v", "K", ":m '<-2<CR>gv=gv")
vim.keymap.set("n", "J", "mzJ`z")
vim.keymap.set("n", "<C-d>", "<C-d>zz")
vim.keymap.set("n", "<C-u>", "<C-u>zz")
vim.keymap.set("n", "<C-H>", "<C-W>h")
vim.keymap.set("n", "<C-J>", "<C-W>j")
vim.keymap.set("n", "<C-K>", "<C-W>k")
vim.keymap.set("n", "<C-L>", "<C-W>l")
vim.keymap.set("n", "q", "<cmd>cclose<cr>", { desc = "Close quickfix list" })

vim.keymap.set('n', '<leader>ccq', function()
    local input = vim.fn.input("Quick Chat: ")
    if input ~= "" then
        require("CopilotChat").ask(input, {
            selection = require("CopilotChat.select").buffer,
            model = "claude-sonnet-4"
        })
    end
end, { desc = "CopilotChat - Quick chat" })

vim.keymap.set('n', '<leader>cc', function()
    require("CopilotChat").open({
        model = "claude-sonnet-4"
    })
end, { desc = "CopilotChat - Open chat" })

vim.keymap.set('v', '<leader>cv', '<Cmd>CopilotChat<CR>', { desc = "CopilotChat - Open chat with visual selection" })
