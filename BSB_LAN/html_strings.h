#define NEWLINE "" // set to "\n" to aid javascript debugging, set to "" to save space in transfer to client

// The following strings contain html/css/javascript code that has been manually indented; don't let automatic indent break this!
// *INDENT-OFF*

const char svg_favicon[] =
  "<svg class='logo' viewBox='0 0 400 400' xmlns='http://www.w3.org/2000/svg'>"
    "<path id='b' d='m98 47-63 1c-6 0-12 4-11 11v88c1 5 3 10 10 11l79-1c25-1"
    " 24-53 4-61 11-5 18-49-19-49zM48 72h52c1 10-2 18-11 19l-38 1v22l43-1c14"
    " 0 14 11 14 20H48Z'/>"
    "<use href='#b' x='246'/>"
    "<path d='m268 350 1-100c2-14 14-16 29-1l56 59v-69h25l-1 99c1 12-12 17-22"
    " 7l-63-64v69Zm-65-173c-112 90-67 155-34 173-4-11-7-23-6-38h60c0 29-4 31-8"
    " 40 57-35 42-86 15-112-21-21-32-40-27-63zm-10 81c13 10 18 20 24 30h-48c5-9"
    " 8-18 24-30zM21 239h25v86h77v25l-90-1s-11 1-11-12z M246 47v25h-68c-10"
    " 1-11 18 1 18l47 1c41 3 37 63 2 66l-82 1v-25h77c11 0 12-18"
    " 0-18h-48c-42-5-37-67 0-67z'/>"
  "</svg>";

const char favicon[] = {
  0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
  0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x08, 0x06, 0x00, 0x00, 0x00, 0x1F, 0xF3, 0xFF,
  0x61, 0x00, 0x00, 0x01, 0xDD, 0x49, 0x44, 0x41, 0x54, 0x38, 0x8D, 0xA5, 0x91, 0x3D, 0x6B, 0x22,
  0x51, 0x14, 0x86, 0xAF, 0xC4, 0x60, 0xB0, 0x50, 0xA6, 0xF0, 0x23, 0xE0, 0x60, 0x0A, 0x09, 0x04,
  0x52, 0xDA, 0xDB, 0x68, 0xEA, 0xF9, 0x11, 0x23, 0xA4, 0xF1, 0x07, 0x58, 0x5B, 0x0A, 0x16, 0x16,
  0x0E, 0x36, 0x26, 0x69, 0x75, 0xBA, 0xA0, 0x85, 0x36, 0x62, 0x27, 0x29, 0x45, 0xC1, 0x0F, 0x10,
  0x14, 0x8B, 0xC9, 0x80, 0x95, 0x82, 0x88, 0x73, 0x9F, 0x14, 0xB2, 0xC3, 0x4A, 0x66, 0xB3, 0x0B,
  0xFB, 0xC2, 0x29, 0xCE, 0xE1, 0xE1, 0xB9, 0x5C, 0x5E, 0xC1, 0x7F, 0x46, 0x00, 0x6C, 0x36, 0x1B,
  0x96, 0xCB, 0x25, 0xCB, 0xE5, 0x92, 0xFD, 0x7E, 0x0F, 0xC0, 0xE1, 0x70, 0x70, 0x6F, 0xAB, 0xD5,
  0x8A, 0x3F, 0x71, 0x62, 0xBB, 0xDD, 0x72, 0x75, 0x75, 0x85, 0xAA, 0xAA, 0xA8, 0xAA, 0x4A, 0x32,
  0x99, 0x64, 0xB7, 0xDB, 0x91, 0x4A, 0xA5, 0xDC, 0x5B, 0x3A, 0x9D, 0xC6, 0x8B, 0x73, 0x1C, 0x07,
  0xF1, 0xF9, 0xF9, 0x89, 0xA2, 0x28, 0x18, 0x86, 0x41, 0xB9, 0x5C, 0x46, 0x51, 0x14, 0xD6, 0xEB,
  0x35, 0x8A, 0xA2, 0x50, 0xAB, 0xD5, 0x30, 0x0C, 0x83, 0x7E, 0xBF, 0x8F, 0x17, 0x77, 0x21, 0xD0,
  0x75, 0x1D, 0x5D, 0xD7, 0xB9, 0xBD, 0xBD, 0x65, 0x38, 0x1C, 0xF2, 0xF6, 0xF6, 0x46, 0x3E, 0x9F,
  0x47, 0xD7, 0x75, 0xE2, 0xF1, 0x38, 0xBD, 0x5E, 0xCF, 0x93, 0x13, 0xB6, 0x6D, 0x73, 0x7D, 0x7D,
  0x8D, 0xA6, 0x69, 0x68, 0x9A, 0x46, 0x22, 0x91, 0xA0, 0xD1, 0x68, 0xB8, 0xBB, 0xA6, 0x69, 0x44,
  0x22, 0x11, 0x06, 0x83, 0xC1, 0x37, 0xEE, 0xFD, 0xFD, 0x1D, 0x21, 0xA5, 0xA4, 0xDD, 0x6E, 0x63,
  0x9A, 0x26, 0xA6, 0x69, 0xD2, 0xED, 0x76, 0xD9, 0xED, 0x76, 0xEE, 0x6E, 0x9A, 0x26, 0xA3, 0xD1,
  0x08, 0x2F, 0x4E, 0x4A, 0x79, 0x6E, 0xC1, 0x2B, 0x52, 0x4A, 0xEA, 0xF5, 0x3A, 0x9B, 0xCD, 0xE6,
  0xEF, 0x35, 0x7A, 0xE5, 0xE5, 0xE5, 0x05, 0x9F, 0xCF, 0x47, 0xAB, 0xD5, 0xFA, 0x59, 0xB0, 0xDD,
  0x6E, 0x69, 0x34, 0x1A, 0x17, 0xC7, 0xD9, 0x6C, 0xC6, 0xCD, 0xCD, 0x0D, 0x42, 0x08, 0xC2, 0xE1,
  0x30, 0x1F, 0x1F, 0x1F, 0x58, 0x96, 0x45, 0xB3, 0xD9, 0x44, 0x4A, 0xE9, 0x3E, 0x60, 0xDB, 0x36,
  0x62, 0x3A, 0x9D, 0x72, 0x7F, 0x7F, 0x7F, 0x21, 0x28, 0x14, 0x0A, 0x08, 0x21, 0x78, 0x7E, 0x7E,
  0x26, 0x16, 0x8B, 0x91, 0x4A, 0xA5, 0xE8, 0x74, 0x3A, 0x08, 0x21, 0x30, 0x0C, 0x03, 0x80, 0x87,
  0x87, 0x07, 0x46, 0xA3, 0x91, 0xB7, 0x20, 0x97, 0xCB, 0x11, 0x0A, 0x85, 0x28, 0x95, 0x4A, 0x3C,
  0x3D, 0x3D, 0x21, 0x84, 0xA0, 0x5A, 0xAD, 0xF2, 0xF8, 0xF8, 0xC8, 0xDD, 0xDD, 0x1D, 0xAF, 0xAF,
  0xAF, 0xDF, 0x05, 0x8E, 0xE3, 0xB8, 0x53, 0x28, 0x14, 0xC8, 0x64, 0x32, 0x94, 0x4A, 0x25, 0x8A,
  0xC5, 0x22, 0x81, 0x40, 0x80, 0x66, 0xB3, 0x49, 0x36, 0x9B, 0x65, 0x3E, 0x9F, 0xA3, 0xAA, 0x2A,
  0xC1, 0x60, 0xF0, 0x2C, 0x58, 0xAD, 0x56, 0xF8, 0xFD, 0x7E, 0x84, 0x10, 0xEE, 0x9F, 0x2D, 0xCB,
  0xA2, 0x52, 0xA9, 0x00, 0x30, 0x99, 0x4C, 0x30, 0x0C, 0x83, 0x6E, 0xB7, 0x4B, 0x36, 0x9B, 0x05,
  0x60, 0x3C, 0x1E, 0x13, 0x8D, 0x46, 0x59, 0x2C, 0x16, 0xE7, 0x16, 0xA4, 0x94, 0x17, 0x03, 0xE0,
  0x38, 0x0E, 0x00, 0xA7, 0xD3, 0x89, 0xDF, 0x99, 0x5F, 0x39, 0x1E, 0x8F, 0x3F, 0xD7, 0xF8, 0xAF,
  0xF9, 0x02, 0x05, 0xC4, 0x09, 0xEE, 0x49, 0x43, 0x56, 0x4E, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45,
  0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82
};

const char graph_html[] =
#ifdef USE_ADVANCED_PLOT_LOG_FILE
#ifndef DEFAULT_DAYS_TO_PLOT // old BSB_LAN_config.h w/o this definition?
#define DEFAULT_DAYS_TO_PLOT "1"
#endif
#ifndef D3_LIBRARY_PATH
#define D3_LIBRARY_PATH "https://d3js.org/d3.v4.min.js"
#endif
#ifndef C3_LIBRARY_PATH
#define C3_LIBRARY_PATH "https://cdn.jsdelivr.net/npm/c3"
#endif
  // - example datalog.txt (/D) contents: -
  // Milliseconds;Date;Parameter;Description;Value;Unit
  // 364592808;01.05.2022 00:00:15;8005;Status Kessel;25;
  // 364593010;01.05.2022 00:00:15;8314;Kesselrücklauftemperatur Ist;66.7;°C
  // [...]
  // to alleviate d3+c3 performance issues when dealing with large datasets, we (allow to) filter those datasets
  // for d3+c3 by using a date range a-b (on start-up: DEFAULT_DAYS_TO_PLOT days back from current date only):
  "<a href>" MENU_TEXT_DDO "</a> " NEWLINE // link to download displayed data a-b (set in code below)
  "<input type='date' onchange='f()'>" NEWLINE // a
  "<output></output>" NEWLINE                  // i ('! - !')
  "<input type='date' onchange='f()'>" NEWLINE // b
  "</td></tr></tbody></table>" NEWLINE // close table opened by surrounding html to escape its width limitation
  "<div id='c3'></div>" NEWLINE
  "<style>" NEWLINE
    "input{width:auto;text-align:right}" NEWLINE // the preceding html has set width=100% :/
    "svg,.c3-tooltip{font:10px sans-serif}" NEWLINE
    "div path,line{fill:none;stroke:#aaa}" NEWLINE
    ".c3-focused{opacity:1;stroke-width:2px}" NEWLINE
    ".c3-defocused,.c3-legend-item-hidden{opacity:0.5 !important}" NEWLINE
    ".c3-tooltip{opacity:0.7;background-color:#eee}" NEWLINE
    "th{background-color:#ccc}" NEWLINE
    ".value{text-align:right}" NEWLINE
  "</style>" NEWLINE
  "<script src='" D3_LIBRARY_PATH "'></script>" NEWLINE
  "<script src='" C3_LIBRARY_PATH "'></script>" NEWLINE
  "<script>" NEWLINE
    "let al='x',bl," NEWLINE // al..bl = data range a..b loaded (i.e. already in RAM)
        "t,h,d=document,l=d.links," NEWLINE // t=datalog text contents, h=href for /Da,b
        "c,n,e='%Y-%m-%d %H:%M'," NEWLINE // c=C3 plot, n=now date, e=date format
        "[a,b]=d.querySelectorAll('input')," NEWLINE
        "i=d.querySelector('output');" NEWLINE
    // get min/max date available in datalog:
    "fetch('DA').then(r=>r.text()).then(c=>{" NEWLINE
      "a.min=b.min=c;" NEWLINE
      "fetch('DB').then(r=>r.text()).then(c=>{" NEWLINE
        "a.max=b.max=c;" NEWLINE
        "n=new Date();" NEWLINE // today
        "b.value=new Date(n.getTime()-60000*n.getTimezoneOffset())" NEWLINE // local date/time
                        ".toISOString().substring(0,10);" NEWLINE // extract date part
        "a.value=new Date((new Date(b.value))" NEWLINE
                          // subtract default-1 days (there's 86400000==24*60*60*1000 ms in a day):
                          "-(" DEFAULT_DAYS_TO_PLOT "-1)*86400000)" NEWLINE // minus on Date converts to epoch!
                        ".toISOString().substring(0,10);" NEWLINE // extract date part
        "f()" NEWLINE // ...and do initial plot
      "})" NEWLINE
    "});" NEWLINE  
    "function f(){" NEWLINE
      "i.textContent='" MENU_TEXT_DLD "';" NEWLINE
      // also change the url used on this page to download just the displayed data:
      "h=l[l.length-1].href='D'+a.value+','+b.value;" NEWLINE
      "if(a.value<al||b.value>bl)" NEWLINE // only load from server if not already in memory
        "fetch(h).then(r=>r.text()).then(c=>{" NEWLINE
          // abbreviate heading to save javascript code size:
          "t=c.replace(/.+/,'m;t;p;d;v;u')" NEWLINE
             // change date format for easy comparison: dd.mm.yyyy -> yyyy-mm-dd:
             ".replace(/(\\d\\d)\\.(\\d\\d)\\.(\\d{4})/g,'$3-$2-$1');" NEWLINE
          "al=a.value;" NEWLINE
          "bl=b.value" NEWLINE
        "}).then(()=>g());" NEWLINE
      "else g()" NEWLINE
    "}" NEWLINE
    "function g(){" NEWLINE  
      // use '!' next to a/b date input fields to signal when there's more (or less):
      "i.textContent=(a.value==a.min?'':'!')+' - '+" NEWLINE
                    "(b.value==b.max?'':'!');" NEWLINE
      // 'pivot' data (p=params, r=row, o=all, x=prevDate, y=prevMs):
      "let p=[],r=[],o=[],x=y=0,k;" NEWLINE
      "d3.dsvFormat(';').parse(t).forEach(function(i){" NEWLINE
        "if(a.value<i.t&&i.t<b.value+'x'){" NEWLINE  // only when t=date is in a...b range
          // the log interval is limited by bsb-lan to be >=10s, therefore
          // start new hh:mm if ms is at least 10000 greater than ...
          // ... or smaller than (due to a device reset) its previous value:
          "if(y&&(i.m-y>9999||i.m-y<0)){o.push(r);r=[];x=i.t}" NEWLINE
          "y=i.m;" NEWLINE
          "k=i.p+' - '+i.d;" NEWLINE
          "if(i.u)k+=' ['+i.u+']';" NEWLINE
          "p[k]=1;" NEWLINE
          "r[k]=i.v;" NEWLINE
          "r['t']=x?x:i.t" NEWLINE
        "}" NEWLINE
      "});" NEWLINE
      "o.push(r);" NEWLINE
      // plot:
      "c=c3.generate({" NEWLINE
        "bindto:'#c3'," NEWLINE
        "data:{" NEWLINE
          "json:o," NEWLINE
          "keys:{x:'t',value:Object.keys(p)}," NEWLINE
          "xFormat:e+':%S'" NEWLINE
        "}," NEWLINE
        "point:{show:false}," NEWLINE
        "axis:{x:{type:'timeseries',tick:{count:3,format:e}}}," NEWLINE
        "zoom:{enabled:true}," NEWLINE
        "size:{height:window.innerHeight-20}," NEWLINE
        "onresize:function(){c.resize({height:window.innerHeight-20})}" NEWLINE
      "})" NEWLINE
    "}" NEWLINE
  "</script>" NEWLINE
  "<table><tbody><tr><td>" NEWLINE // re-open table for surrounding html
  ;
#else // #ifdef USE_ADVANCED_PLOT_LOG_FILE
/*
  Based on the awesome tutorials at
    https://bl.ocks.org/d3noob
    https://bl.ocks.org/larsenmtl
  Thanks a lot for your great work!
*/
"<style>" /* set the CSS */

"div path {"
  "stroke: steelblue;"
  "stroke-width: 2;"
  "fill: none;"
"}"

".axis path,"
".axis line {"
  "fill: none;"
  "stroke: grey;"
  "stroke-width: 1;"
  "shape-rendering: crispEdges;"
"}"

".legend {"
  "font-size: 16px;"
  "font-weight: bold;"
  "text-anchor: middle;"
"}"

"</style>"
// load the d3.js library
"<script src=\"http://d3js.org/d3.v3.min.js\"></script>"

"<script>"

// Set the dimensions of the canvas / graph
"var margin = {top: 30, right: 20, bottom: 70, left: 50},"
"width = 1000 - margin.left - margin.right,"
"height = 600 - margin.top - margin.bottom;"

// Parse the date / time
"var parseDate = d3.time.format(\"%d.%m.%Y %H:%M:%S\").parse;"

// Set the ranges
"var x = d3.time.scale().range([0, width]);"
"var y = d3.scale.linear().range([height, 0]);"

// Define the axes
"var axisTimeFormat = d3.time.format.multi(["
  "[\".%L\", function(d) { return d.getMilliseconds(); }],"
  "[\":%S\", function(d) { return d.getSeconds(); }],"
  "[\"%H:%M\", function(d) { return d.getMinutes(); }],"
  "[\"%H:%M\", function(d) { return d.getHours(); }],"
  "[\"%d.%m\", function(d) { return d.getDay() && d.getDate() != 1; }],"
  "[\"%m.%Y\", function(d) { return d.getDate() != 1; }],"
  "[\"%B\", function(d) { return d.getMonth(); }],"
  "[\"%Y\", function() { return true; }]"
 "]);"

"var xAxis = d3.svg.axis().scale(x)"
    ".orient(\"bottom\").ticks(5)"
    ".tickFormat(axisTimeFormat);"

"var yAxis = d3.svg.axis().scale(y)"
    ".orient(\"left\").ticks(5);"

// Define the line
"var priceline = d3.svg.line()  "
  ".x(function(d) { return x(d.Date); })"
  ".y(function(d) { return y(d.Value); });"

// Get the data
"var dsv = d3.dsv(\";\", \"text/plain\");"
"dsv(\"D\", function(data) {"

  "data.forEach(function(d) {"
    "d.Date = parseDate(d.Date);"
    "d.Value = +d.Value;"
      "});"

// Scale the range of the data
  "x.domain(d3.extent(data, function(d) { return d.Date; }));"
  "y.domain([d3.min(data, function(d) { return d.Value; }), d3.max(data, function(d) { return d.Value; })]);"

// Nest the entries by symbol
      "var dataNest = d3.nest()"
          ".key(function(d) {return d.Parameter + ' - ' + d.Description;})"
          ".entries(data);"

// Adds the svg canvas
"var svg = d3.select(\"div\")"
    ".append(\"svg\")"
     ".attr(\"width\", width + margin.left + margin.right)"
     ".attr(\"height\", height + margin.top + margin.bottom + dataNest.length/4 * 15)"
   ".append(\"g\")"
     ".attr(\"transform\", \"translate(\" + margin.left + \",\" + margin.top + \")\");"

  "var color = d3.scale.category10();"   // set the colour scale

  "legendSpace = width/dataNest.length;" // spacing for the legend

// Loop through each symbol / key
  "dataNest.forEach(function(d,i) {"

    "svg.append(\"path\")"
            ".attr(\"class\", \"line\")"
            ".style(\"stroke\", function() {" // Add the colours dynamically
                    "return d.color = color(d.key); })"
      ".attr(\"id\", 'tag'+d.key.replace(/\\s+/g, ''))" // assign ID
      ".attr(\"d\", priceline(d.values));"

// Add the Legend
    "svg.append(\"text\")"
                ".attr(\"x\", (margin.left + legendSpace/2 + (i % 4) * width / 4))"  // space legend
                ".attr(\"y\", height + (margin.bottom/2)+ 5 + Math.floor(i/4)*20)"
                ".attr(\"class\", \"legend\")"    // style the legend
                ".style(\"fill\", function() {" // Add the colours dynamically
                    "return d.color = color(d.key); })"
      ".on(\"click\", function(){"
// Determine if current line is visible 
        "var active   = d.active ? false : true,"
        "newOpacity = active ? 0 : 1;"
// Hide or show the elements based on the ID
        "d3.select(\"#tag\"+d.key.replace(/\\s+/g, ''))"
          ".transition().duration(100)"
          ".style(\"opacity\", newOpacity); "
// Update whether or not the elements are active
        "d.active = active;"
      "})"
      ".text(d.key); "
  "});"

  "var mouseG = svg.append(\"g\")"
  ".attr(\"class\", \"mouse-over-effects\");"

  "mouseG.append(\"path\")" // this is the black vertical line to follow mouse
    ".attr(\"class\", \"mouse-line\")"
    ".style(\"stroke\", \"black\")"
    ".style(\"stroke-width\", \"1px\")"
    ".style(\"opacity\", \"0\");"

  "var lines = document.getElementsByClassName('line');"

  "var mousePerLine = mouseG.selectAll('.mouse-per-line')"
    ".data(dataNest)"
    ".enter()"
    ".append(\"g\")"
    ".attr(\"class\", \"mouse-per-line\");"

  "mousePerLine.append(\"circle\")"
    ".attr(\"r\", 7)"
    ".attr(\"id\", function(d) {"
      "return 'tag'+d.key.replace(/\\s+/g, '')" // assign ID
    "})"
    ".style(\"stroke\", function(d) {"
      "return color(d.key);"
    "})"
    ".style(\"fill\", \"none\")"
    ".style(\"stroke-width\", \"1px\")"
    ".style(\"opacity\", \"0\");"

  "mousePerLine.append(\"text\")"
    ".attr(\"id\", function(d) {"
      "return 'tag'+d.key.replace(/\\s+/g, '')" // assign ID
    "})"
    ".attr(\"transform\", \"translate(10,3)\");"

  "mouseG.append('svg:rect')" // append a rect to catch mouse movements on canvas
    ".attr('width', width)" // can't catch mouse events on a g element
    ".attr('height', height)"
    ".attr('fill', 'none')"
    ".attr('pointer-events', 'all')"
    ".on('mouseout', function() {" // on mouse out hide line, circles and text
      "d3.select(\".mouse-line\")"
        ".style(\"opacity\", \"0\");"
      "d3.selectAll(\".mouse-per-line circle\")"
        ".style(\"opacity\", \"0\");"
      "d3.selectAll(\".mouse-per-line text\")"
        ".style(\"opacity\", \"0\");"
    "})"
    ".on('mouseover', function() {" // on mouse in show line, circles and text
      "d3.select(\".mouse-line\")"
        ".style(\"opacity\", \"1\");"
      "d3.selectAll(\".mouse-per-line circle\")"
        ".style(\"opacity\", function(d) {"
          "return d.active ? 0 : 1;"
        "});"
      "d3.selectAll(\".mouse-per-line text\")"
        ".style(\"opacity\", function(d) {"
          "return d.active ? 0 : 1;"
        "});"
    "})"
    ".on('mousemove', function() {" // mouse moving over canvas
      "var mouse = d3.mouse(this);"
      "d3.select(\".mouse-line\")"
        ".attr(\"d\", function() {"
          "var d = \"M\" + mouse[0] + \",\" + height;"
          "d += \" \" + mouse[0] + \",\" + 0;"
          "return d;"
        "});"

      "d3.selectAll(\".mouse-per-line\")"
        ".attr(\"transform\", function(d, i) {"
          "var xDate = x.invert(mouse[0]),"
          "bisect = d3.bisector(function(d) { return d.Date; }).right;"
          "idx = bisect(d.values, xDate);"

          "var beginning = 0,"
          "end = lines[i].getTotalLength(),"
          "target = null;"

          "while (true){"
            "target = Math.floor((beginning + end) / 2);"
            "pos = lines[i].getPointAtLength(target);"
            "if ((target === end || target === beginning) && pos.x !== mouse[0]) {"
              "break;"
            "}"
            "if (pos.x > mouse[0]) end = target;"
            "else if (pos.x < mouse[0]) beginning = target;"
            "else break;" //position found
          "}"

          "outputFormat = d3.time.format(\"%H:%M:%S\");"
          "d3.select(this).select('text')"
          ".text(d.values[idx].Value + \" (\" + outputFormat(d.values[idx].Date) + \")\");"

          "return \"translate(\" + mouse[0] + \",\" + pos.y +\")\";"
        "});"
  "});"

// Add the X Axis
  "svg.append(\"g\")"
    ".attr(\"class\", \"x axis\")"
    ".attr(\"transform\", \"translate(0,\" + height + \")\")"
    ".call(xAxis);"

// Add the Y Axis
  "svg.append(\"g\")"
    ".attr(\"class\", \"y axis\")"
    ".call(yAxis);"

// Add the X Grid
"svg.append(\"g\").attr(\"class\", \"grid\").attr(\"transform\", \"translate(0,\" + height + \")\").call(xAxis.tickSize(-height, 0, 0).tickFormat(\"\"));"
// Add the Y Grid -  -  -  -  -
"svg.append(\"g\").attr(\"class\", \"grid\").style(\"stroke-dasharray\", \"1 3\").call(yAxis.ticks(20).tickSize(-width, 0, 0).tickFormat(\"\"));"
// Add the Y Grid  ------------
"svg.append(\"g\").attr(\"class\", \"grid\").call(yAxis.ticks(10).tickSize(-width, 0, 0).tickFormat(\"\"));"

"});"

"</script>";
#endif // #ifdef USE_ADVANCED_PLOT_LOG_FILE

const char header_html[] =
  "\n"
  "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\">" NEWLINE
  "<html><head>" NEWLINE
  "<meta http-equiv=\"content-type\" content=\"text/html;charset=UTF-8\">" NEWLINE
  "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1.0,minimum-scale=1.0\">" NEWLINE
  "<link rel=\"icon\" type=\"image/svg+xml\" href=\"/favicon.svg\">" NEWLINE
  "<title>BSB-LAN</title>" NEWLINE
  "<style>A{text-decoration:none}A:visited,active{color:blue}A:hover{color:red;background-color:yellow}A:focus{color:red}" NEWLINE
  "a.logo:hover{background-color:initial;text-decoration:initial}" NEWLINE
  "table{width:100%;max-width:1024px;margin:auto}" NEWLINE
  "td{vertical-align:top}" NEWLINE
  "td.header{vertical-align:middle}" NEWLINE
  "svg.logo{width:10%;height:10%}" NEWLINE
  "input{width:100%;box-sizing:border-box}select{width:100%}</style>" NEWLINE
  "</head><body>";
const char header_html2[] =
  "<script>function set(p){" NEWLINE
    "var v=document.getElementById('value'+p).value.replace(/\\.$/,'')" NEWLINE
          ".replaceAll(' ','_')" NEWLINE
          ".replace('---','');" NEWLINE
    "window.open(document.getElementById('main_link').href+'S'+p+'='+v,'_self')" NEWLINE
  "}" NEWLINE
  "function setbit(p){" NEWLINE
    "var x=document.getElementById('value'+p),v,i;" NEWLINE
    "for(v=i=0;i<x.options.length;i++)" NEWLINE
      "if(x.options[i].selected)" NEWLINE
        "v=v+eval(x.options[i].value);" NEWLINE
    "window.open(document.getElementById('main_link').href+'S'+p+'='+v,'_self')" NEWLINE
  "}</script>";
const char header_html3[] =
  "<font face='Arial'>"
  "<center>";

const char auth_req_html[] =
  "WWW-Authenticate: Basic realm=\"Secure Area\"\n"
  "Connnection: close\n"
  "\n"
  "<!DOCTYPE HTML>"
  "<HTML><HEAD><TITLE>BSB-LAN</TITLE>"
  "</HEAD><BODY><H1>401 Unauthorized.</H1></BODY></HTML>";

// *INDENT-ON*

#if defined(ESP32)
const char* serverIndex = "<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";
#endif
