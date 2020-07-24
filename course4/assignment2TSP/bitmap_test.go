package main

import (
	"testing"
)

func TestSet(t *testing.T) {
	b := BitMap(0)
	got := b.Set(0)
	want := BitMap(1)
	if got != want {
		t.Errorf("got %v want %v", got, want)
	}
}

func TestClear(t *testing.T) {
	b := BitMap(1)
	got := b.Clear(0)
	want := BitMap(0)
	if got != want {
		t.Errorf("got %v want %v", got, want)
	}
}

func TestIsSet(t *testing.T) {
	b := BitMap(1)
	got := b.IsSet(0)
	want := true
	if got != want {
		t.Errorf("got %v want %v", got, want)
	}
}

func TestString(t *testing.T) {
	b := BitMap(1)
	got := b.String()
	want := "0001"
	if got != want {
		t.Errorf("got %v want %v", got, want)
	}
}
