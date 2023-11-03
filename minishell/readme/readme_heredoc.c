command_prompt~  infile < |  grep a // invalid command since < must preceed a word
//zsh: parse error near `|'


command_prompt~ << bob cat // bob is the heredoc eof. the heredoc is cat in stdout
heredoc> BOB
heredoc> bob
heredoc>  bob
heredoc> bob
BOB
bob
 bob

//each EOF is respected bob, lol, fred, bresil
command_prompt~ << bob << lol cat > /dev/stdout| << fred << bresil cat > /dev/stdout
pipe heredoc> BOB
pipe heredoc> bob
pipe heredoc> LOL
pipe heredoc> lol
pipe heredoc> FRED
pipe heredoc> fred
pipe heredoc> Bresil
pipe heredoc> bresil
BOB
LOL
BOB
LOL
FRED
Bresil
command_prompt~ bash

/******************************/
/************BASH**************/
/*****************************/


command_prompt~  << bob << lol cat > /dev/stdout| << fred << bresil cat > /dev/stdout
> Bob
> bob
> Lol
> lol
> Fred
> fred
> Bresil
> bresil
Bresil



command_prompt~  << bob << lol cat > a | << fred << bresil cat > b
> Bob
> bob
> Lol
> lol
> Fred
> fred
> Bresil
> bresil
command_prompt~ cat a
Lol
command_prompt~ cat b
Bresil

command_prompt~ > c < a cat < b
command_prompt~ cat c
Bresil

command_prompt~ mv c a
command_prompt~ cat a
Bresil
command_prompt~ < a cat >c << bob
> bobob
> bob
command_prompt~ cat c
bobob
command_prompt~ cat a
Bresil
command_prompt~ << EOF
> FDS
> FSD
> EOF
command_prompt~ << EOF cat
> FDS
> FSD
> EOF
FDS
FSD




Ce que j'ai compris

entre DQUOTE les $ restent valides.

je dois creer un fichier caché qui sera écrasé par chaque heredoc de tel sorte que lorsque je
vais faire appel à ce fichier il corresponde directement a la redirection valide.

NOTE: si une commande contient plusieurs redirection de même type, seule la dernière redirection est valide
ex:
command_prompt> < a cat >c << bob
> bobob
> bob
