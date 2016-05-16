OBJECTS = XMLSerializable.o Entity.o Item.o Ammunition.o Armor.o Consumable.o Creature.o Food.o Gold.o main.o Potion.o Scroll.o Spellbook.o Wand.o Weapon.o

HEADERS = XMLSerializable.h Entity.h Item.h Ammunition.h Armor.h Consumable.h Creature.h Food.h Gold.h main.h Potion.h Scroll.h Spellbook.h Wand.h Weapon.h

prog1: $(OBJECTS)
	g++ $^ -o prog1

%.o: %.cpp $(HEADERS)
	g++ -std=c++0x -c $< -o $@

clean:
	rm -f *.o prog1