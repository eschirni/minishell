# minishell - As beautiful as a shell
## [@eschirni](https://github.com/eschirni) and [@tzeck](https://github.com/tzeck1)<br>
<img width="225" alt="Screenshot 2022-02-28 at 3 29 02 PM" src="https://user-images.githubusercontent.com/65648486/156000211-bfae73ac-9cb0-4d34-a87e-a539b32f5b10.png">

## Description of the subject
Thanks to Minishell, you’ll be able to travel through time and come back to problems
people faced when Windows didn’t exist. <br> <br>
We have restrictions which functions we're allowed to use (see [subject pdf](https://github.com/tzeck1/minishell/files/8154030/minishell.pdf)). In addition we have to format our code according to the schools [Norm](https://github.com/tzeck1/minishell/files/8154641/norm.pdf)
#### **Full subject:** [minishell.pdf](https://github.com/tzeck1/minishell/files/8154030/minishell.pdf) <br>

## Installation
1. You might have to install the readline libary with `brew install readline` <br>
2. To create the execuatable run `make` <br>
3. To start the programm: `./minishell`

## What we've implemented
**-Own functions:**
cd, pwd, env, exit, unset, export, echo (all other bash commands are implemented with execv)<br>
**-A working history:**
arrow key up/down <br>
**-Single and double Quotes** <br>
**-Redirections:**
< (input), > (trunc), >> (append) and << (heredoc) <br>
**-Pipes:**
single and multible pipe(s), combination with redirections possible <br>
**-Environment Variables** <br> 
**-Signals:**
ctrl-C, ctrl-D and ctrl-\ <br>

## Structure
**1. Lexer:** tokenization of the input string e.g. "CMD, ARGUMENT, PIPE, CMD, ARGUMENT, TRUNC, FILE" <br>
**2. Parser:** filtering parser errors and quotes, redirects output for pipes and redirections, etc. <br>
**3. Executor:** executes commands with arguments
