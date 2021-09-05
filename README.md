# queryt
API keyless YouTube querying tool in C

This program makes a quick youtube query of a inputted query and uses the [libcurl](https://curl.se/libcurl/) libraries to download the full HTML page and scrape the query json form the HTML, then uses [json-c](https://github.com/json-c/json-c) libraries to search for videos array and displays this videos information according to user passed arguments.

## Dependencies

* [libcurl](https://curl.se/libcurl/) *(curl)*
* [json-c](https://github.com/json-c/json-c) *(present on most linux distros)*

## How to use

### Install

`sudo make clean install`

### Usage

`queryt -s <search query>`

### Commands

* **-f, --format**	-	uses format modifiers to customize the output **\[aditRT\]**
* **-m, --max**		-	defines the max number of displayed results
* **-s, --search**	-	search content on youtube
* **-h, --help**	-	display this help and exit
* **-v, --version**	-	output version information and exit

#### Format Modifiers

* **a**	author
* **d**	duration or video length
* **i**	video id
* **t**	title
* **R**	return
* **T**	tab

### Example

`queryt -s "Never Gonna Give You Up" -m 5 -f iTaTdRt`

Search for the video "Never Gonna Give You Up" sets the max results to 5 and formats it by showing the information by this order:

\[video id\] *tab* \[author\] *tab* \[duration\] *return* \[title\]

## Limitations

Due to the way youtube json's are formatted, without an API key, the program is limitted to get 21 search results in best case scenario.
