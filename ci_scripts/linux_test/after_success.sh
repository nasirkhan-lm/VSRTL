# /bin/sh

# Fail on failing QTest execution
set -e

# Execute unit tests
find . -executable -type f -name "tst_*" | while read line; do
    ($line)
done

# Create lcov report
# capture coverage info
lcov --directory . --capture --output-file coverage.info
# filter out system and extra files.
# To also not include test code in coverage add them with full path to the patterns: '*/tests/*'
lcov --remove coverage.info '/usr/*' "${HOME}"'/.cache/*' --output-file coverage.info
# output coverage data for debugging (optional)
lcov --list coverage.info
# Uploading to CodeCov
# '-f' specifies file(s) to use and disables manual coverage gathering and file search which has already been done above
bash <(curl -s https://codecov.io/bash) -f coverage.info || echo "Codecov did not collect coverage reports"
