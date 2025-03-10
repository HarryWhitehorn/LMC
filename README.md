# LMC

[LMC Wiki](https://en.wikipedia.org/wiki/Little_man_computer)

Example programs can be found in /programs.

## Menus

- File
    - Open
        - Open a `.txt` into the editor
        - Open a `.lmc` into memory (and reset)
    - Exit
        - Exit program
- Control
    - Run
        - Start `lmc` mainloop
    - Stop
        - Stop `lmc` mainloop
    - Step
        - Step `lmc` PC counter
    - Reset
        - Step all memory and registers to zero
- Editor
    - Editor
        - Opens the plaintext editor (see [Editor](#editor))
- Settings
    - Settings
        - Opens the settings menu (see [Settings](#settings))
- Help
    - Docs
        - Opens [readme.md](#lmc)
    - About
        - Open about popup

## Editor

### Menu

- File
    - Open
        - Opens a `.txt` into the editor
    - Save
        - Save current editor content as a `.txt`
        - Save current editor content as a `.lmc`
    - Close
        - Hides the editor
- Load
    - Load
        - Loads the `.txt` editor content into the `lmc` memory as `.lmc`

## Settings

- Delay
    - Change delay timing (0ms for no delay) [`default: 200ms`]
- Output
    - Toggle auto-append char(s) to end of output w/ char(s) input (`\n` for newline) [`default: true && '\n'`]
    - Toggle auto-clear on reload/load [`default: false`]
    - Clear output now
    - Toggle autoscroll [`default: true`]
- Palette
    - Toggle PC Highlight w/ color select [`default: true && red`]
    - Toggle AR Highlight w/ color select [`default: true && green`]


