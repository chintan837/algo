package main

import (
	"bufio"
	"flag"
	"fmt"
	"log"
	"math"
	"os"
	"strconv"
	"strings"
)

// Point ...
type Point struct{ x, y int }

func (p *Point) String() string {
	return fmt.Sprintf("x: %d y: %d", p.x, p.y)
}

// ParseFile ...
func ParseFile(fileName string) (int, []Point) {
	file, err := os.Open(fileName)
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	scanner.Scan()
	n, err := strconv.Atoi(scanner.Text())
	if err != nil {
		log.Fatal(err)
	}
	points := make([]Point, 0)
	for scanner.Scan() {
		wordScanner := bufio.NewScanner(strings.NewReader(scanner.Text()))
		wordScanner.Split(bufio.ScanWords)
		var p Point
		for wordScanner.Scan() {
			p.x, err = strconv.Atoi(wordScanner.Text())
			if err != nil {
				log.Fatal(err)
			}
			wordScanner.Scan()
			p.y, err = strconv.Atoi(wordScanner.Text())
			if err != nil {
				log.Fatal(err)
			}
		}
		if err := wordScanner.Err(); err != nil {
			log.Fatal(err)
		}
		// fmt.Println(p.String())
		points = append(points, p)
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

	return n, points
}

// Dist ...
func Dist(a, b int, points []Point) float64 {
	if len(points) < 2 {
		return 0
	}
	return math.Hypot(float64(points[a].x-points[b].x),
		float64(points[a].y-points[b].y))
}

// Tsp calculates the minimum distance path to visit all points one and only
// once
func Tsp(points []Point) float64 {
	n := len(points)
	if n < 2 {
		return 0
	}
	prev := make(map[BitMap]map[int]float64)
	bm := BitMap(1)
	for i := 1; i < n; i++ {
		c := bm
		c.Set(i)
		m := make(map[int]float64)
		m[i] = Dist(0, i, points)
		prev[c] = m
	}
	for m := 3; m <= n; m = m + 1 {
		// fmt.Println("m: ", m)
		// calculate sets of size m that have bit 0 set
		curr := make(map[BitMap]map[int]float64)
		for p := range prev {
			for j := 0; j < n; j++ {
				newBm := p
				newBm.Set(j)
				if newBm == p {
					continue
				}
				_, ok := curr[newBm]
				if !ok {
					curr[newBm] = make(map[int]float64)
				}
			}
		}

		// for all sets of size m
		for s := range curr {
			// fmt.Printf("\t%v\n", s.String())
			// for each j in s and j≠0 calculate the tsp for that set
			for j := 1; j < n; j++ {
				if s.IsSet(j) {
					c := s
					c.Clear(j)
					// fmt.Printf("\t\tj: %d, c: %s\n", j, c.String())
					// d := dist(c, i, points)
					// calculate minimum for A[s][ckj]
					minDist := math.MaxFloat64
					for k := 1; k < n; k++ {
						if c.IsSet(k) {
							// fmt.Printf("\t\t\t\tk: %d", k)
							dist := prev[c][k] + Dist(j, k, points)
							// fmt.Printf(" dist: %f (%f + %f)\n", dist, prev[c][k], Dist(j, k, points))
							if dist < minDist {
								minDist = dist
							}
						}
					}
					curr[s][j] = minDist
					// fmt.Printf("\t\t\t\tA[%s][%d]: %f\n", s.String(), j, minDist)
				}
			}
			// fmt.Println()
		}

		prev = curr
	}

	tsp := math.MaxFloat64
	for i := range prev {
		// fmt.Println(i, m)
		for j, val := range prev[i] {
			dist := Dist(0, j, points) + val
			if dist < tsp {
				tsp = dist
			}
		}
	}

	return tsp
}

func main() {
	filename := flag.String("f", "", "command -f <input filename>")
	flag.Parse()

	n, points := ParseFile(*filename)
	fmt.Printf("Number of nodes: %d\n", n)
	for _, p := range points {
		fmt.Println(p.String())
	}
	d := make(map[Point]map[Point]float64)
	for i := range points {
		d[points[i]] = make(map[Point]float64)
		for j := range points {
			d[points[i]][points[j]] = math.Hypot(float64(points[i].x-points[j].x),
				float64(points[i].y-points[j].y))
			fmt.Printf("%f\t", d[points[i]][points[j]])
		}
		fmt.Println()
	}

	fmt.Println(Tsp(points))
}
