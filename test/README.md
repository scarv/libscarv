
# `libscarv` Tests

This file gives a brief description for the `libscarv` tests, such as they
are.

---

## Organisation

Each of the algorithms implemented in libscarv has a test associated
with it.
The test is kept in `tests/<algorithm>/test_<algorithm>.c`

Each test runs the algorithm multiple times for different inputs and
outputs.
- For each input/output pair, the test prints this to `stdout`.
- To verify the correctness of the implementation, the piped output is
  written to a file, then fed to a python script which checks the correctness
  of the results.

Each test is also benchmarked for how many 'cycles' it takes to
execute, and how many instructions are retired while executing it.
