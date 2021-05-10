# AFL-Fuzz Demo

This is a very brief demo; the AFL-Fuzz [docs][docs] are really good and well
worth a read.

## Setup

For simplicity these instructions all run in a known root directory
(`$AFL_ROOT`).

```shell
export AFL_ROOT=path/to/some/root
```

## Building AFL-Fuzz

Fortunately AFL is very easy to build and install:

```shell
cd $AFL_ROOT
cd AFL
make -j`nproc`
DESTDIR=$AFL_ROOT/install make install
```

You can probably also get it from your system package manager.

## Structure of a Fuzzable Program

This is all in the [AFL Quickstart Guide][guide], but for reference:
* Write program harnesses that read bytes from `stdin` or a file and interpret
  them somehow.
* Include some behaviour that crashes the program (e.g. assertions that can
  fail, or sanitiser crashes such as undefined behaviour).
* Supply any relevant seed inputs.

## Running the Demos

```shell
cd $AFL_ROOT
git clone git@github.com:mob-group/afl-demo.git
cd afl-demo
export AFL_PATH=$AFL_ROOT/install/usr/local/lib/afl

# Compile the code using the AFL compiler wrapper
$AFL_ROOT/install/usr/local/bin/afl-gcc \
  -fsanitize=undefined \
  -fsanitize-undefined-trap-on-error \
  sum_n.c -o sum_n

$AFL_ROOT/install/usr/local/bin/afl-gcc \
  versions.c -o versions

# Run the fuzzer
$AFL_ROOT/install/usr/local/bin/afl-fuzz \
  -i inputs \
  -o sum_n_outputs \
  ./sum_n

$AFL_ROOT/install/usr/local/bin/afl-fuzz \
  -i inputs \
  -o versions_outputs \
  ./versions
```

## Interpreting Results

Once you've killed the fuzzer with `ctrl-C`, you can look at the results in each
of the output directories. For each, AFL generates a `crashes/` and `queue/`
directory with input files that you can use directly as input to the previously
compiled programs. The ones in `queue/` are valid inputs that don't produce a
crash.

You'll find that AFL is able to identify quite quickly that large positive and
any negative inputs cause `sum_n` to integer overflow, and that it cannot find
an input that distinguishes `sum_n` and `sum_n_v2` at all (as you'd expect!).

[docs]: https://github.com/google/AFL/blob/master/README.md
[guide]: https://github.com/google/AFL/blob/master/docs/QuickStartGuide.txt
