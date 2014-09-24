
#ifndef bits_h
#define bits_h

	#define bit_isset( field, pos ) (field & (1 << pos))

	#define bit_set( field, pos ) field |= (1 << pos);

	#define bit_unset( field, pos ) field &= ~(1 << pos);

	#define bit_invert( field, pos ) field ^= (1 << pos);

#endif

