/* Purpose of this script is to check whether count of constructor calls is the
   same as destructors in the just run C++ app.

   Input:
   Stdout from the C++ app.

   Requirements:
   The scripts looks for output lines starting with either `+` (for
   constructors) or `~` (for destructors) and identifies them by the memory
   address included in those lines as well, in a format of `0x<hex_digits>`.
 */

const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
    terminal: false
});

const logEntries = [];

rl.on('line', (line) => {
    logEntries.push(parseLine(line));
});

rl.once('close', () => {
    const analysis = analyzeConstructorsDeconstructors(logEntries);

    console.log(`\nFound ${analysis.matched.length} constructors with matching destructors.`);

    if (analysis.unmatched.length > 0) {
        console.log(`\nFound ${analysis.unmatched.length} constructors WITHOUT matching destructors:\n`);
        for (const item of analysis.unmatched) {
            console.log(item);
        }
    } else {
        console.log(`\nFound 0 constructors without matching destructors.`);
    }
});

////////////////////////////////////////////////////////////////////////////////

function parseLine(line) {
    const logEntry = {
        type: "other",
        address: null,
        originalLine: line,
    };

    if (line.startsWith("+ ")) {
        logEntry.type = "constructor";
    }
    if (line.startsWith("~ ")) {
        logEntry.type = "deconstructor";
    }

    if (logEntry.type !== "other") {
        const matches = /0x[0-9a-f]+/.exec(line);
        logEntry.address = matches?.[0] ?? null;
    }

    return logEntry;
}

function analyzeConstructorsDeconstructors(logEntries) {
    const analysis = {
        matched: [],
        unmatched: [],
    };

    const entriesByAddresses = new Map();

    // Try to match constructors with deconstructors first:
    //
    for (const entry of logEntries) {
        if (entry.type === "other") {
            // do nothing
        } else if (entry.type === "constructor") {
            if (!entry.address) {
                console.log(`Failed to extract an address: '${entry.originalLine}'`);
            } else {
                if (entriesByAddresses.has(entry.address)) {
                    console.log(`Found a new constructor on the already taken address: '${entry.originalLine}'`);
                } else {
                    entriesByAddresses.set(entry.address, entry);
                }
            }
        } else if (entry.type === "deconstructor") {
            if (!entry.address) {
                console.log(`Failed to extract an address: '${entry.originalLine}'`);
            } else {
                if (entriesByAddresses.has(entry.address)) {
                    const matchingConstructorEntry = entriesByAddresses.get(entry.address);
                    analysis.matched.push(matchingConstructorEntry.originalLine);
                    entriesByAddresses.delete(entry.address);
                } else {
                    console.log(`Unexpected deconstructor without a matching constructor: '${entry.originalLine}'`)
                }
            }
        } else {
            console.log(`Unexpected entry type '${entry.type}': '${entry.originalLine}'`);
        }
    }

    // Then gather all unmatched constructors:
    //
    for (const entry of entriesByAddresses.values()) {
        analysis.unmatched.push(entry.originalLine);
    }

    return analysis;
}