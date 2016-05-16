Dungeon Crawler

INFO:
Adjust screen to 100x26 characters to show up correctly

	In game
	------------------------------------------------
	w/a/s/d    -> Movement/Attack
	z          -> Wait
	p          -> Pickup item from ground
	i          -> View Inventory
	t          -> Toss item from inventory
	u          -> Use item (from ground or inventory)
	f          -> Turn on/off lantern
	x          -> Enter ethereal realm
	UP Arrow   -> View earlier messages
	Down Arrow -> View more recent messages

	Menus
	------------------------------------------------
	ENTER      -> Confirm choice
	ARROW KEYS -> Choose selection
	

I chose tiles for positioning because that allowed me to have an
inventory space for items on the ground as well as to quickly
determine whether monsters were on that space without have to
loop through a vector of items and creatures.  It also allowed
me to quickly check which tiles can be visible and walkable
for later stages in this project when I work on sight range.
