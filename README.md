# Pipex

Duplicate the behaviour of command:
```
<file1 cmd1 | cmd2> file2
```
and also:
```
<< LIMITER | cmd1 | cmd2> b
```

To run it with only 2 commands,
Simply git clone and type 'MAKE' in your terminal, then:

```
./pipex file1 cmd1 cmd2 file2
```

To run it with multiple pipes and also the heredoc:
simply git clone and type 'Make bonus' in your terminal, then:

```
./pipex file1 cmd1 cmd2 cmd3 cmd4 ....cmdn file2
```

OR

```
./pipex here_doc LIMITER cmd1 cmd2 cmd3 .....cmdn file2
```
