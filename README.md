## kanban-fetch

Fetches data from OmniFocus.app for display in a kanban-like system.

### How do I install it?

1. Download or `clone` it:

```
git clone https://github.com/jyruzicka/kanban-fetch.git
```

2. Build it
3. Copy the target to your favoured `bin` directory.

Alternatively, grab the binary [from 1klb](http://1klb.com/projects/kanban-fetch).

### How do I run it?

Navigate to it in terminal and run:

```
./kanban-fetch --help
```

to see all possible options. To test it out, run something like:

```
./kanban-fetch -d --out=foo.db
```

This will output the data to a SQLite database "foo.db" in the same directory as the binary, and also give you a bunch of debug information.

### How do I run it regularly?

Add it to your LaunchAgents. I recommend [Lingon](http://www.peterborgapps.com/lingon/) to make the whole process painless.

### What do I do once I've got a database of projects?

That's entirely up to you, but I recommend checking out [this project](https://github.com/jyruzicka/kanban) for an example.