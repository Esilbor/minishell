# Bash Environment Variables & Export Command Cheat Sheet

## Default Environment Variables

- `PWD`: The path of the current working directory.
- `SHLVL`: The shell level, useful for nested shells (increments with each subshell).
- `_`: The last command that was executed, starts as `/usr/bin/env` after a clean environment launch.

## Exporting Variables

- **Export Variable without Value**:
  - `export VARIABLE=`: Marks an existing or new VARIABLE for export to the environment.
- **Set and Export Variable with Value**:
  - `export VARIABLE=value`: Sets the VARIABLE to a value and exports it.
- **Invalid export**:
  - `export VAR1 VAR2` is invalid but `VAR1= VAR2=` is valid (must contain '=')
- **List All Exported Variables**:
  - `export`: Lists all current exported environment variables with their values.

## Modifying Variable Values

- **Clear Variable Value**:
  - `export VARIABLE=`: Clears the value of VARIABLE (sets it to an empty string).
- **Change Variable Value**:
  - `export VARIABLE=newvalue`: Sets VARIABLE to a new value.
- **Append to Variable Value**:
  - `export VARIABLE+=append`: Appends 'append' to the existing value of VARIABLE.

## Rules for Variable Names

- **Valid Names**:
  - Can include letters, digits, and underscores.
  - Must not begin with a digit.
- **Invalid Names**:
  - Cannot include special characters like `?`, `*`, `-`, etc.
  - Cannot start with a digit (e.g., `9var` is invalid).
- **Examples of Valid Identifiers**:
  - `VAR`, `VAR_1`, `_VAR`, `VAR123`
- **Examples of Invalid Identifiers**:
  - `2VAR`, `VAR-NAME`, `e?`, `8`

## Special Cases

- **Underscore Variable**:
  - `export _`: The underscore `_` is a valid environment variable name but usually contains the last executed command. It's generally not recommended to overwrite it.

## Common Mistakes

- Trying to export variables with invalid names results in a `not a valid identifier` error.
- Forgetting to assign a value with the export command does not show up in the export list.

## General Notes

- Changes to environment variables in a script or session are local to that session unless exported to a broader scope, like in the user's profile or system environment.
- Always check your variable names for compliance with naming rules to avoid errors.


# Environment Variable Naming Rules

When setting environment variables in Unix-like operating systems, there are specific naming conventions that must be followed. Violating these conventions may result in errors or undefined behavior. Here are the rules that govern the naming of environment variables:


## Rules for Valid Environment Variable Names:

1. **Alphanumeric and Underscore Only**:
   - Variable names can contain only letters (`A-Z`, `a-z`), digits (`0-9`), and underscores (`_`).

2. **Non-Digit First Character**:
   - The first character of a variable name must be a letter or an underscore, not a digit.

3. **No Special Characters**:
   - Special characters such as `=`, `-`, `+`, `.`, `:`, `/`, `\`, and spaces are not allowed within variable names.

4. **Case Sensitivity**:
   - Variable names are case-sensitive, so `VARNAME`, `VarName`, and `varname` would be considered distinct.

5. **Avoid Reserved Keywords**:
   - Reserved shell keywords and names of important environment variables should be avoided unless intentional overriding is required.

## Examples:

### Valid Variable Names:
- `VARNAME`
- `_VARNAME`
- `VAR_NAME1`

### Invalid Variable Names:
- `2VARNAME` - Invalid because it starts with a digit.
- `VAR-NAME` - Invalid because it contains a dash.
- `VAR.NAME` - Invalid because it contains a dot.
- `VAR NAME` - Invalid because it contains a space.
- `VAR+NAME` - Invalid because it contains a plus.
- `VAR=NAME` - Invalid because it contains an equal sign, which is reserved for assignment.

Remember that following these naming conventions is important for ensuring that your environment variables work correctly in scripts and terminal sessions.
