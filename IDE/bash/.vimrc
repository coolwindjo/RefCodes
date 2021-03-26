set shiftwidth=4
set tabstop=4
set ruler
set visualbell
set scrolloff=5
highlight linernr ctermbg=darkblue
set expandtab
set smarttab
set softtabstop=4
set showcmd
set cursorline
set wildmenu 	" visual autocomplete for command menu
set lazyredraw  " redraw only when we need to.
set showmatch
set laststatus=2
set cindent
set smartindent
set autoindent
set hi=1000
set title
"set mouse=a
set hls
set scs
colorscheme evening
colorscheme elflord
colorscheme murphy
syntax on
filetype plugin indent on
set nobackup
set tags=tags;/
set ignorecase
set smartcase
set ai
set nu
map<F2> gT
map<F3> gt
map<F4> :w <CR> :! gcc -g -lm -Wall % && ./a.out<CR>
map<F5> :w <CR> :! g++ % -O2 -lm -std=c++11 && time ./a.out && rm -rf ./a.out*<CR>
map<F6> :w <CR> :! python %<CR>
map<F10> :e ++enc=euc-kr<CR> :set fileencoding=utf-8<CR> :set f=unix<CR>
set pastetoggle=<F9>

