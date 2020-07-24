package main

import "testing"

func TestPrintln(t *testing.T) {
	p := Point{x: 0, y: 0}
	got := p.String()
	want := "x: 0 y: 0"
	if got != want {
		t.Errorf("got %v want %v", got, want)
	}
}

func TestParseFile(t *testing.T) {
	n, points := ParseFile("test")
	if n != 5 {
		t.Errorf("got %v want %v %v", n, 5, points)
	}
	expected := []Point{Point{3, 2}, Point{16, 10}, Point{0, 0}, Point{9, 7}, Point{9, 16}}
	for p := range points {
		if expected[p] != points[p] {
			t.Errorf("got %v want %v", points[p], expected[p])
		}
	}
}

func TestTsp(t *testing.T) {
	got := Tsp([]Point{})
	want := float64(0)
	if got != want {
		t.Errorf("got %v want %v", got, want)
	}
}

func BenchmarkTsp(b *testing.B) {
	_, points := ParseFile("test")
	b.Log("Running TSP benchmark")
	for i := 0; i < b.N; i++ {
		Tsp(points)
	}
}

func TestDist(t *testing.T) {
	got := Dist(0, 1, []Point{Point{2, 2}, Point{10, 10}})
	want := 11.313708498984761
	if got != want {
		t.Errorf("got %v want %v", got, want)
	}
}
