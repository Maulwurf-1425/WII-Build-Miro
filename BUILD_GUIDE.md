# MiroTayWorkshop RPG - Build & Play Guide

## What's in this build

### Zones
| Zone | How to reach |
|---|---|
| **Overworld** | Starting area - street with all buildings |
| **Miro's House** | Walk to the brown house (top-left), press A at door |
| **Miro's Room** | Go upstairs inside Miro's House |
| **Tay's House** | Walk to the blue house (bottom-left), press A at door |
| **Tay's Room** | Go upstairs inside Tay's House |
| **Skatepark** | Top-right corner, press A at entrance |
| **The Workshop** | Bottom-right - LOCKED until Tay learns all 6 tricks |

### NPCs (total: 11)
- **Overworld**: Jae, Leo, Finn
- **Miro's House**: Miro's Dad, Miro's Mom
- **Tay's House**: Tay's Mom
- **Miro's Room**: Band Poster (interactive)
- **Tay's Room**: Workbench (interactive)
- **Skatepark**: Kira, Dev, Skatepark Dude

### The Skate Teaching Mechanic
- Go to the Skatepark with both players
- Miro (P1) moves close to Tay, then press A
- A timing bar appears - Tay (P2) presses A to land the trick
- 6 tricks to learn: Ollie → Manual → Kickflip → Heelflip → 50-50 Grind → Noseslide
- After all 6: **The Workshop unlocks** in the overworld (bottom-right)

### The Plot Twist
- Once the Workshop unlocks, both players go inside and walk to the center
- The ending reveals Tay has been secretly building a half-pipe all summer
- 6 pages of story dialogue between Miro and Tay

---

## Step 1 — Install devkitPro (on your PC)

Go to: https://devkitpro.org/wiki/Getting_Started

**Windows:** Download and run the devkitPro installer  
**macOS/Linux:** Use the dkp-pacman package manager

After installing, open a terminal and run:
```
dkp-pacman -S devkitPPC wii-dev ppc-libpng ppc-zlib
```

Set these environment variables (add to your `.bashrc` or `.zshrc`):
```bash
export DEVKITPRO=/opt/devkitpro
export DEVKITPPC=$DEVKITPRO/devkitPPC
export PATH=$PATH:$DEVKITPPC/bin
```

**Windows:** Set these in System → Advanced → Environment Variables instead.

---

## Step 2 — Install GRRLIB (graphics library)

In your terminal:
```bash
git clone https://github.com/GRRLIB/GRRLIB.git
cd GRRLIB/GRRLIB
make
```

Now move the GRRLIB folder so it sits next to your game folder:
```
your-folder/
  GRRLIB/               <- the cloned repo
  MiroTayWorkshop RPG/   <- this project
```

If you put GRRLIB somewhere else, edit the `LIBDIRS` line in `Makefile`.

---

## Step 3 — Add a logo image (optional but looks good)

Create a PNG image (any size, purple background, white text) and save it as:
```
MiroTayWorkshop RPG/data/logo.png
```

The build system auto-converts it to a C header (`logo_png.h`).  
If you skip this step, comment out the `#include "logo_png.h"` line and the
`GRRLIB_LoadTexture(logo_png)` block in `main.c` - the logo screen will just
show the purple background and text, which still works fine.

---

## Step 4 — Build

```bash
cd MiroTayWorkshop RPG
make
```

If it works you'll see `MiroTayWorkshop RPG.dol` appear in the folder.  
That's the actual Wii binary.

### Common errors:
| Error | Fix |
|---|---|
| `libgrrlib.a not found` | Fix LIBDIRS path in Makefile |
| `wiiuse/wpad.h not found` | Run `dkp-pacman -S wii-dev` again |
| `libpng not found` | Run `dkp-pacman -S ppc-libpng ppc-zlib` |
| `logo_png.h not found` | Add a logo.png to data/ or comment out that include |

---

## Step 5 — Put it on your Wii (SD card method)

1. Get an SD card and put it in your computer
2. Create this folder structure:
```
SD card root/
  apps/
    MiroTayWorkshop RPG/
      boot.dol        <- rename your built .dol to this
      meta.xml        <- see below
      icon.png        <- 128x48 pixels, shows in HBC menu (optional)
```

3. Create `meta.xml`:
```xml
<app version="1">
  <name>MiroTayWorkshop RPG</name>
  <coder>Miro and Tay</coder>
  <version>0.2</version>
  <release_date>20260823000000</release_date>
  <short_description>Co-op teen RPG</short_description>
  <long_description>
    Miro teaches Tay to skate. Tay builds something in secret.
    Two best friends, one summer.
  </long_description>
</app>
```

4. Put the SD card in your Wii, launch Homebrew Channel
5. The game will appear in the HBC app list - launch it!

---

## Step 6 — Faster testing (WiFi push)

If your Wii and PC are on the same WiFi network, you can push the .dol
directly from PC to Wii without touching the SD card every time:

On your Wii: open Homebrew Channel, note its IP address (shown at the top)  
On your PC:
```bash
export WIILOAD=tcp:192.168.x.x    # your Wii's IP
wiiload MiroTayWorkshop RPG.dol
```

`wiiload` comes with devkitPro. This is the fastest way to iterate.

---

## Step 7 — WBFS / USB Loader GX (if you want it as a "disc game")

Normally homebrew runs from the `apps/` folder. If you specifically want it
to appear in USB Loader GX as a disc-style game, you need to wrap the .dol
in a fake Wii disc image. This is optional and more complicated:

1. Install **Wiimms ISO Tools** (`wit`) from: https://wit.wiimm.de/
2. You'll need a minimal Wii disc template (the community calls this
   "dol2iso" - search WiiBrew forums for the current method, as the exact
   tool that works has changed over the years)
3. Basic command with wit once you have a template:
```bash
wit copy --id MTWR01 MiroTayWorkshop RPG.dol MiroTayWorkshop RPG.wbfs
```

The `apps/` method in Step 5 is easier, more compatible, and is how 99% of
Wii homebrew is actually run - I'd recommend that over WBFS unless you
specifically need USB Loader GX disc-mode.

---

## Controls (both Wiimotes held sideways / horizontal)

| Button | Action |
|---|---|
| D-Pad | Move your character |
| A | Interact, confirm, trigger skate lesson |
| B | Cancel, go back, exit zone |
| HOME | Quit to Homebrew Channel |

Miro = Wiimote 1 (P1)  
Tay = Wiimote 2 (P2)

---

## What to build next

The skeleton is ready. In order of effort:

1. **Sprite art** - replace colored rectangles with real character PNGs loaded via `GRRLIB_LoadTexture`
2. **Skate mini-game depth** - make the timing window shrink as trick difficulty increases
3. **Dialogue tree** - add proper branching dialogue with choices
4. **More NPCs** - add Sam, more park friends, a skate shop owner
5. **MTB section** - a trail area for both characters' shared MTB skill
6. **Music/jam mini-game** - rhythm game for Miro's guitar/drums and Tay's flute
7. **Save data** - write progress to SD card via libfat
