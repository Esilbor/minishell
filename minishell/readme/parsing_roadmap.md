# Roadmap for `PARSING` Part in Minishell

## **Introduction**
In this roadmap, we focus on parsing user inputs into structured command data to be passed to the Execution component. Your job is to break down raw command strings into actionable commands, arguments, and flags while managing special characters and their implications.

## **1. Setting Up the Basic Structure**
- **Goal**: Prepare for tokenization.
- **Tasks**:
    1. Define structures to hold command information, including command name, arguments, redirections, pipes, etc.
    2. Coordinate with the Execution teammate to ensure these structures match their needs.

## **2. Tokenization**
- **Goal**: Break the user input into meaningful chunks (tokens).
- **Tasks**:
    1. Split the input based on spaces, but be cautious about spaces within quotes.
    2. Consider special characters like `$`, `|`, `<`, `>`, and treat them as unique tokens or modify the following token as required.

## **3. Handling Quotes**
- **Goal**: Properly interpret and store strings within single (`'`) and double (`"`) quotes.
- **Tasks**:
    1. When encountering a quote, search for its closing pair.
    2. For double quotes, handle the special case of `$` inside them.

## **4. Handling Redirections and Pipes**
- **Goal**: Detect and store redirection (`<`, `>`, `<<`, `>>`) and pipe (`|`) symbols.
- **Tasks**:
    1. For each symbol, store the associated file or command.
    2. Ensure ordering (e.g., command followed by output redirection).

## **5. Environment Variable Expansion**
- **Goal**: Replace `$VARIABLE_NAME` structures with their corresponding values.
- **Tasks**:
    1. When encountering `$`, search for the end of the variable name (which might be a space, special character, etc.).
    2. Replace `$VARIABLE_NAME` with its value from the environment or from local variables if you've implemented them.

## **6. Handling Special Variables (e.g., `$?`)**
- **Goal**: Recognize special shell variables and set them up for processing by the Execution component.
- **Tasks**:
    1. Detect the `$?` symbol.
    2. Prepare it for expansion to the exit status of the most recently executed command during the execution phase.

## **7. Integration with Execution Component**
- **Goal**: Ensure smooth handoff of parsed data to the Execution component.
- **Tasks**:
    1. Define a clear method or API to pass parsed command structures to Execution.
    2. Coordinate with the Execution teammate for testing and integration.

## **8. Error Handling**
- **Goal**: Provide clear error messages for unsupported or incorrect command structures.
- **Tasks**:
    1. Check for unclosed quotes.
    2. Validate redirections (e.g., ensure there's a filename after `>`).
    3. Produce relevant error messages for any parsing issues.

## **9. Testing and Refinement**
- **Goal**: Ensure robust parsing for a variety of input scenarios.
- **Tasks**:
    1. Test with simple commands and gradually increase complexity.
    2. Test edge cases, especially with quotes, redirections, and special characters.
    3. Collaborate with the Execution teammate for integrated tests.

---

This roadmap is focused on ensuring that the parsing part correctly breaks down and interprets user commands while facilitating a seamless transition to the execution phase. Regular communication with the Execution teammate is essential to ensuring that the parsed structures are correctly understood and executed.
