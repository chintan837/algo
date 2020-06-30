package main

import (
	"bufio"
	"flag"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

type Point struct { x, y int }

func (p *Point)Println() {
    fmt.Printf("x: %d y: %d\n", p.x, p.y)
}

func parseFile(fileName string) (int, []Point) {
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
            p.y, err = strconv.Atoi(wordScanner.Text())
            if err != nil {
                log.Fatal(err)
            }
	    }
	    if err := wordScanner.Err(); err != nil {
		    log.Fatal(err)
	    }
        // p.Println()
        points = append(points, p)
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

    return n, points
}

func main() {
    filename := flag.String("f", "", "command -f <input filename>")
    flag.Parse()
    n , points := parseFile(*filename)
	fmt.Printf("Number of nodes: %d\n", n)
    for i := range points {
        points[i].Println()
    }
}
