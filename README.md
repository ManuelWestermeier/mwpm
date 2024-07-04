# mwpm

The Manuel Westermeier Package Menager

## setup

clone repo using 

```bash
git clone https://github.com/ManuelWestermeier/mwpm.git 
```

build it and set the executable in your path variable

## usage

usable with github repos

https://github.com/ManuelWestermeier/next-gen-exe-test.git >> next-gen-exe-test@ManuelWestermeier

### short

```txt
usage:

mwpm {folder} {command} {...}
mwpm {folder} {install | i} {repo}@{githubUser}
mwpm {folder} {update | u} {repo}@{githubUser}
mwpm {folder} {remove | r} {repo}@{githubUser}
mwpm {folder} {packages | p} {u | i | r}

exemple: mwpm . i next-gen-exe-test@ManuelWestermeier
```

#### install

```bash
mwpm . {i or install} {repo}@{user}
```

#### remove

```bash
mwpm . {r or remove} {repo}@{user}
```

#### update

```bash
mwpm . {u or update} {repo}@{user}
```

#### install app packages from "pkg.mwpm"

u = update all
i = install all
r = remove all

```bash
mwpm . {p or packages} {u = or i or r}
```

pkg.mwpm file
```txt
# syntax for comments
# 100% empty lines are allowed too

at-script@ManuelWestermeier
next-gen-exe-test@ManuelWestermeier
```