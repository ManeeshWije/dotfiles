vim.api.nvim_create_autocmd('TextYankPost', {
    desc = 'Highlight when yanking (copying) text',
    group = vim.api.nvim_create_augroup('kickstart-highlight-yank', { clear = true }),
    callback = function()
        vim.highlight.on_yank()
    end,
})

vim.api.nvim_create_autocmd("LspAttach", {
    group = vim.api.nvim_create_augroup('lsp-attach', { clear = true }),
    callback = function(event)
        local map = function(keys, func, desc)
            vim.keymap.set("n", keys, func, { buffer = event.buf, desc = "LSP: " .. desc })
        end

        map("fe", vim.diagnostic.open_float, "Open Diagnostic Float")
        map("K", vim.lsp.buf.hover, "Hover Documentation")
        map("gs", vim.lsp.buf.signature_help, "Signature Documentation")
        map("gD", vim.lsp.buf.declaration, "Goto Declaration")
        map("gd", vim.lsp.buf.definition, "Goto Definition")
        map("gr", vim.lsp.buf.references, "Goto References")
        map("<leader>ca", vim.lsp.buf.code_action, "Code Action")
        map("<leader>rn", vim.lsp.buf.rename, "Rename all references")
        map("<leader>v", "<cmd>vsplit | lua vim.lsp.buf.definition()<cr>", "Goto Definition in Vertical Split")
        map("<leader>p", function() require("conform").format({ async = true, lsp_fallback = true }) end, "Format Document")
        map("<leader>fn", function() vim.diagnostic.jump({ count = 1 }) end, "Next Diagnostic")
        map("<leader>fp", function() vim.diagnostic.jump({ count = -1 }) end, "Previous Diagnostic")

        local function client_supports_method(client, method, bufnr)
            if vim.fn.has 'nvim-0.11' == 1 then
                return client:supports_method(method, bufnr)
            else
                return client.supports_method(method, { bufnr = bufnr })
            end
        end

        local client = vim.lsp.get_client_by_id(event.data.client_id)
        if client and client_supports_method(client, vim.lsp.protocol.Methods.textDocument_documentHighlight, event.buf) then
            local highlight_augroup = vim.api.nvim_create_augroup('lsp-highlight', { clear = false })

            -- When cursor stops moving: Highlights all instances of the symbol under the cursor
            -- When cursor moves: Clears the highlighting
            vim.api.nvim_create_autocmd({ 'CursorHold', 'CursorHoldI' }, {
                buffer = event.buf,
                group = highlight_augroup,
                callback = vim.lsp.buf.document_highlight,
            })
            vim.api.nvim_create_autocmd({ 'CursorMoved', 'CursorMovedI' }, {
                buffer = event.buf,
                group = highlight_augroup,
                callback = vim.lsp.buf.clear_references,
            })

            -- When LSP detaches: Clears the highlighting
            vim.api.nvim_create_autocmd('LspDetach', {
                group = vim.api.nvim_create_augroup('lsp-detach', { clear = true }),
                callback = function(event2)
                    vim.lsp.buf.clear_references()
                    vim.api.nvim_clear_autocmds { group = 'lsp-highlight', buffer = event2.buf }
                end,
            })
        end
    end,

})

vim.api.nvim_create_augroup("vimStartup", { clear = true })
vim.api.nvim_create_autocmd("BufReadPost", {
    group = "vimStartup",
    callback = function()
        local last_position = vim.fn.line([['"]])
        local last_line = vim.fn.line("$")
        local filetype = vim.bo.filetype

        if last_position >= 1 and last_position <= last_line and not filetype:match("commit") then
            vim.cmd('normal! g`"')
        end
    end,
})

vim.api.nvim_create_autocmd("BufEnter", {
    pattern = "copilot-*",
    callback = function()
        vim.keymap.set("n", "<C-L>", "<C-W>l", { noremap = true, silent = true, buffer = true })
        vim.keymap.set("i", "<C-L>", "<C-\\><C-N><C-W>l", { noremap = true, silent = true, buffer = true })
        vim.keymap.set("n", "<C-C>", function()
            require("CopilotChat").reset()
        end, { desc = "CopilotChat - Reset chat" })
        vim.keymap.set('i', '<S-Tab>', 'copilot#Accept("<Tab>")', { silent = true, expr = true })
    end,
})

vim.api.nvim_create_augroup("remember_folds", { clear = true })
vim.api.nvim_create_autocmd("BufWinLeave", {
    group = "remember_folds",
    pattern = "?*",
    command = "mkview 1",
})
vim.api.nvim_create_autocmd("BufWinEnter", {
    group = "remember_folds",
    pattern = "?*",
    command = "silent! loadview 1",
})
