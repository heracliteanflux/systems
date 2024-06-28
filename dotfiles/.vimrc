"   .vimrc
"
" use `:help <mapping>` to get information on a mapping
" you today
" use `:source`         to effect changes made to this file
"
" vim-plug :   https://github.com/junegunn/vim-plug





" HELP -------------------------------------------------------------- {{{
"
"
"
" i                enter edit mode
" Esc              enter command mode
" 0                move the cursor to the beginning of the          line
" Shift-$          move the cursor to the end       of the          line
" o                move the cursor to the beginning of the next     line and enter edit mode
" O                move the cursor to the beginning of the previous line and enter edit mode
" p                move the cursor to the beginning of the next     line and paste
" P                move the cursor to the beginning of the previous line and paste
" r, <C>           replace the character underneath the cursor with character <C>
" Shift-r          type over the line until you hit Esc
" s                delete  the character underneath the cursor and enter edit mode
" Shift-s          delete  the active line, move the cursor to the beginning of the line, and enter edit mode
" x                delete  the character underneath the cursor
"
" w                move the cursor to the beginning of the next word
" W                move the cursor to the beginning of the next word
" e                move the cursor to the end       of the next word
" E                move the cursor to the end       of the next word
" b                move the cursor to the beginning of the previous word
" B                move the cursor to the beginning of the previous word
"
" <N>, j           move <N> lines down
" <N>, k           move <N> lines up
" <N>, h           move <N> characters to the left
" <N>, l           move <N> characters to the right
"
" dd               delete the current line and copy it to the clipboard
" d, 0             delete from the cursor to the beginning of the line
" d, Shift-$       delete from the cursor to the end       of the line
" Shift-D          delete from the cursor to the end       of the line
" 0, Shift-D       delete the current line and leave the line blank
" d, <N>, d        delete <N> lines starting from the current line
"
" yy               copy   the current line
" y, 0             copy   from the cursor to the beginning of the line
" y, Shift-$       copy   from the cursor to the end       of the line
" y, <N>, y        copy   <N> lines starting from the current line
"
" zt               move active line to top    of screen
" zz               move active line to middle of screen
" zb               move active line to bottom of screen
" ZZ               save and exit
"
" gg               go to the beginning of the file
" Shift-g          go to the end       of the file
"
" u                undo
" :undo            undo
" Shift-u          redo
" :redo            redo
"
"
" How to write multiple lines simultaneously?
" 0.               move the cursor to the top-left corner of the multi-line write

" 1. Ctrl-v        enter visual block mode
" 2. <N>, j        move down <N> lines
" 3. Shift-i
" 4.               begin to type across the top line
" 5. Esc           the line should appear on the remaining lines underneath the typed line
"
"
" zo               open  current fold (cursor on top of)
" zc               close current fold (cursor on top of)
" zR               unfold all folds
" zM               refold all folds
"
" Ctrl-u           scroll up   half a page
" Ctrl-d           scroll down half a page
" Ctrl-b           scroll up      one page, cursor to last  line
" Ctrl-f           scroll down    one page, cursor to first line
" Ctrl-e           scroll down    one line, cursor at top    of page
" Ctrl-y           scroll up      one line, cursor at bottom of page
"
" Ctrl-v           enter visual block mode
" Ctrl-w, arrow    move to window
" Ctrl-w, j        move down  a window
" Ctrl-w, k        move up    a window
" Ctrl-w, h        move left  a window
" Ctrl-w, l        move right a window
" Ctrl-w, t        move to top    window
" Ctrl-w, b        move to bottom window
" Shift-a          move cursor to end of line and enter edit mode
" Shift-H          move cursor to top    of screen
" Shift-M          move cursor to middle of screen
" Shift-L          move cursor to bottom of screen
"
" :help <command>  help with vim command
" :source
" :w               save file
" :wall            save all files
" :q               quit file
" :qall            quit all files
" :only            quit all files except the current file
" :wq              save and quit
" :wqall           save and quit all files
" :!<command>      terminal command
" :terminal        terminal
" :split           horizontal window split
" :vsplit          vertical   window split
" :set <option>
" :set <option>?  display current value
" :verbose set <option>?   display more information about value
" :set  all                 display all settings
" :set! all                 display all settings (one per line)
" :options                  display all settings
"
"
" colors
"   https://www.linode.com/docs/guides/vim-color-schemes/
"
" :colorscheme <scheme>
" :colorscheme Ctrl-D       display list of color schemes
"
"
" vim -o file1 file2   horizontal windows
" vim -O file1 file2   vertical   windows
"
"
"
"
"
" https://vi.stackexchange.com/questions/2162/why-doesnt-the-backspace-key-work-in-insert-mode
" https://www.freecodecamp.org/news/vimrc-configuration-guide-customize-your-vim-editor/
" https://stackoverflow.com/questions/9549729/vim-insert-the-same-characters-across-multiple-lines
" https://vi.stackexchange.com/questions/3105/can-i-delete-an-entire-line-except-the-line-break
"
" }}}





" MAPPINGS -------------------------------------------------------------- {{{

" ftplugin
"   use   `:verbose set <option>?` to see whether an option is being set by ftplugin
"   e.g., `:verbose set tw?`
"
" to override ftplugin values
"   create a file, where <type> is something like python,text,vim,etc.   ~/.vim/after/ftplugin/<type>.vim  
"   Homebrew package manager places defaults here:                       /opt/homebrew/Cellar/vim/9.1.0350/share/vim/vim91/ftplugin/
"   see:                                                                 https://vi.stackexchange.com/questions/26169/difference-between-adding-vim-after-ftplugin-vs-vim-ftplugin
"   see:                                                                 https://vi.stackexchange.com/questions/26792/why-wont-vim-source-my-ftplugin-after-vim-file
"
filetype        on        "  enable                      file type detection
filetype plugin on        "  enable and load plugins     for the detected file type
filetype indent on        "             load indentation for the detected file type



set ai                    " (autoindent)
set bs=indent,eol,start   " (backspace) 
                          "   allow backspacing over autoindent
                          "   allow backspacing over line breaks (join lines)
                          "   allow backspacing over the start of insert; CTRL-W and CTRL-U stop once at the start of insert
"set cursorcolumn         "               highlight the cursor col vertically
"set cursorline           "               highlight the cursor row horizontally
set encoding=utf8         "
set et                    " (expandtab)   use spaces instead of tab characters
"set ft                   " (filetype)
setlocal fo-=c            " (formatoptions)
set history=1000          "               the number of commands to save in the history (default 20)
set hlsearch              "               use highlighting while searching
"set nobackup             "               do not save backup files
set nocompatible          "               disable compatibility with vi, which can cause unexpected issues
set nu                    " (number)      display line numbers
set ruler
set si                    " (smartindent)
set sm                    " (showmatch)   show matching words during a search
set sw=2                  " (shiftwidth)
set ts=2                  " (tabstop)
set tw=0                  " this value gets overriden by ftplugin above
set wildmenu              "               enable auto completion menu after pressing Tab
set wildmode=list:longest " make wildmenu behave in a similar fashion to bash completion
set wildignore=*.doc,*.docx,*.jpg,*.png,*.gif,*.pdf,*.pyc,*.exe,*.flv,*.img,*.xls,*.xlsx

"syn en                   " (syntax enable)
syn on                    " (syntax on)   enable syntax highlighting


" }}}





" VIMSCRIPT -------------------------------------------------------------- {{{

" This will enable code folding.
" Use the marker method of folding.
" Use `:help folding` for more information.
augroup filetype_vim
    autocmd!
    autocmd FileType vim setlocal foldmethod=marker
augroup END

" More Vimscripts code goes here.

" }}}





" PLUGINS ---------------------------------------------------------------- {{{
"
" Use `:PlugInstall` to download a new plugin
"
"

call plug#begin('~/.vim/plugged')

Plug 'dense-analysis/ale'     " https://github.com/dense-analysis/ale
Plug 'preservim/nerdtree'     " https://github.com/preservim/nerdtree
"Plug 'Valloric/YouCompleteMe' " https://github.com/ycm-core/YouCompleteMe
                              " https://github.com/ycm-core/YouCompleteMe/issues/1751
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'

call plug#end()

" }}}





" STATUS LINE ------------------------------------------------------------ {{{
"
"    DO NOT USE WHEN USING VIM-AIRLINE PLUGIN

" Clear status line when vimrc is reloaded.
"set statusline=

" Status line left side.
"set statusline+=\ %F\ %M\ %Y\ %R

" Use a divider to separate the left side from the right side.
"set statusline+=%=

" Status line right side.
"set statusline+=\ ascii:\ %b\ hex:\ 0x%B\ row:\ %l\ col:\ %c\ percent:\ %p%%

" Show the status on the second to last line.
"set laststatus=2

" }}}
