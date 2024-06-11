zstyle ':completion:*' list-colors "${(@s.:.)LS_COLORS}"
autoload -Uz compinit
compinit

if [[ "$OSTYPE" == "darwin"* ]]; then
    fpath+=("$(brew --prefix)/share/zsh/site-functions")
fi

export NVM_DIR=~/.nvm
export TERM="xterm-256color"
export EDITOR='nvim'
export VISUAL="nvim"
export HISTSIZE=10000
export SAVEHIST=10000
export HISTDUPE=erase

setopt appendhistory
setopt sharehistory
setopt hist_ignore_space
setopt hist_ignore_all_dups
setopt hist_save_no_dups
setopt hist_ignore_dups
setopt hist_find_no_dups

# Shortcuts
bindkey -v
bindkey '^R' history-incremental-search-backward
bindkey '^p' history-search-backward
bindkey '^n' history-search-forward
bindkey '^H' backward-delete-char
bindkey '^?' backward-delete-char

# git
alias addup='git add -u'
alias addall='git add .'
alias branch='git branch'
alias checkout='git checkout'
alias clone='git clone'
alias commit='git commit -m'
alias fetch='git fetch'
alias merge='git merge'
alias pull='git pull origin'
alias push='git push origin'
alias stats='git status'  # 'status' is protected name so using 'stats' instead
alias tag='git tag'
alias newtag='git tag -a'

alias st='syncthing'
alias sd="cd ~ && cd \$(fd --type d | fzf)"
alias ls='eza --long --header --icons --git'
alias 'ls -a'='eza --long --all --header --icons --git'
alias yy='yazi'
alias cat='bat'

if [[ "$OSTYPE" == "darwin"* ]]; then
    export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
    export PATH="$PATH:/Applications/Docker.app/Contents/Resources/bin/:/Users/maneesh/Library/Python/3.11/bin:/opt/homebrew/opt/postgresql@15/bin:/Users/maneesh/.config/scripts/"
fi

# bun
export BUN_INSTALL="$HOME/.bun"
export PATH="$BUN_INSTALL/bin:$PATH"

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    # bun completions
    [ -s "/home/maneesh/.bun/_bun" ] && source "/home/maneesh/.bun/_bun"
fi


function __zoxide_pwd() {
    \builtin pwd -L
}

function __zoxide_cd() {
    \builtin cd -- "$@"
}

function __zoxide_hook() {
    \command zoxide add -- "$(__zoxide_pwd)"
}

if [[ ${precmd_functions[(Ie)__zoxide_hook]:-} -eq 0 ]] && [[ ${chpwd_functions[(Ie)__zoxide_hook]:-} -eq 0 ]]; then
    chpwd_functions+=(__zoxide_hook)
fi

function __zoxide_z() {
    if [[ "$#" -eq 0 ]]; then
        __zoxide_cd ~
    elif [[ "$#" -eq 1 ]] && { [[ -d "$1" ]] || [[ "$1" = '-' ]] || [[ "$1" =~ ^[-+][0-9]$ ]]; }; then
        __zoxide_cd "$1"
    else
        \builtin local result
        result="$(\command zoxide query --exclude "$(__zoxide_pwd)" -- "$@")" && __zoxide_cd "${result}"
    fi
}

function __zoxide_zi() {
    \builtin local result
    result="$(\command zoxide query --interactive -- "$@")" && __zoxide_cd "${result}"
}

function cd() {
    __zoxide_z "$@"
}

function cdi() {
    __zoxide_zi "$@"
}

if [[ -o zle ]]; then
    __zoxide_result=''

    function __zoxide_z_complete() {
        [[ "${#words[@]}" -eq "${CURRENT}" ]] || return 0

        if [[ "${#words[@]}" -eq 2 ]]; then
            _files -/
        elif [[ "${words[-1]}" == '' ]]; then
            __zoxide_result="$(\command zoxide query --exclude "$(__zoxide_pwd || \builtin true)" --interactive -- ${words[2,-1]})" || __zoxide_result=''

            \builtin bindkey '\e[0n' '__zoxide_z_complete_helper'
            \builtin printf '\e[5n'
        fi

        return 0
    }

    function __zoxide_z_complete_helper() {
        if [[ -n "${__zoxide_result}" ]]; then
            BUFFER="cd ${(q-)__zoxide_result}"
            \builtin zle reset-prompt
            \builtin zle accept-line
        else
            \builtin zle reset-prompt
        fi
    }
    \builtin zle -N __zoxide_z_complete_helper

    [[ "${+functions[compdef]}" -ne 0 ]] && \compdef __zoxide_z_complete cd
fi

eval "$(zoxide init zsh)"

autoload -U promptinit; promptinit

prompt pure
