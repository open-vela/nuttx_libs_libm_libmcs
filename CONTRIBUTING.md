# Contributing to LibmCS

## How Can I Contribute?

### Reporting Bugs

Report bugs by creating a GitLab Issue with the following information:

1. Give the Issue a meaninfull title
2. Write a brief description of the issue you have
3. Describe the issue details answering the following quiestions:
    - What are the steps to reproduce the *bug*?
    - What is the current *bug* behavior?
    - What is the expected *correct* behavior?
    - Relevant logs/screenshots and/or associated data.

We will pick the Issue up and continue its workflow.

### Suggesting Enhancements

Suggest enhancements by creating a GitLab Issue with the following information:

1. Problem to solve
2. Proposal
3. Intended use-case

### Pull Requests

Contribute source code by following the next steps:

1. Fork the repository
2. Create a branch with your code and/or documentation contribution:
    - For the source code format please read the section [Styleguides](#styleguides).
    - Corresponding source code documentation must be added
    - All pipelines must pass
3. Create a merge request on the LibmCS repository

We will pick the Issue up and continue its workflow.

#### Styleguides

To preformat the LibmCS sources we use Astyle. The concrete Astyle options we use are the following:

```
> astyle --style=linux --indent=spaces=4 --break-blocks \
--pad-oper --pad-comma --align-pointer=name --add-brackets \
--convert-tabs --pad-header --unpad-paren \
--indent-preproc-block --indent-preproc-define --max-code-length=99
```

After running Astyle some further formatting may be carried out to adjust the overall readability.

