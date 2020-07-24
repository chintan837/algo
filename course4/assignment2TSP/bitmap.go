package main

import (
	"fmt"
)

// BitMap ...
type BitMap uint32

// Set sets the bit 0 - n-1
func (s *BitMap) Set(n int) BitMap {
	*s = *s | (1 << n)
	return *s
}

// Clear clears the bit n
func (s *BitMap) Clear(n int) BitMap {
	*s = *s & ^(1 << n)
	return *s
}

// IsSet checks if bit is set
func (s BitMap) IsSet(n int) bool {
	return s&(1<<n) != 0
}

// String returns BitMap formatted as string
func (s BitMap) String() string {
	return fmt.Sprintf("%04b", s)
}
