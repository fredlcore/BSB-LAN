#define NEWLINE "" // set to "\n" to aid javascript debugging, set to "" to save space in transfer to client

// The following strings contain html/css/javascript code that has been manually indented; don't let automatic indent break this!
// *INDENT-OFF*

const char svg_favicon[] =
  "<svg class='logo' viewBox='0 0 400 400' xmlns='http://www.w3.org/2000/svg'"
    " style='background-color:#fff'>"  // instead of transparent, for visibility in dark themes
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
  0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x10, 0x10, 0x10, 0x00, 0x01, 0x00, 0x04, 0x00, 0x28, 0x01,
  0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00,
  0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x40, 0x42, 0x40, 0x00, 0x80, 0x83, 0x81, 0x00, 0x93, 0x96, 0x94, 0x00, 0xa7, 0xaa,
  0xa8, 0x00, 0xb0, 0xb3, 0xb1, 0x00, 0xbe, 0xc1, 0xbe, 0x00, 0xc3, 0xc7, 0xc4, 0x00, 0xcb, 0xcf,
  0xcc, 0x00, 0xd2, 0xd6, 0xd3, 0x00, 0xe2, 0xe5, 0xe3, 0x00, 0xea, 0xed, 0xeb, 0x00, 0xf0, 0xf4,
  0xf1, 0x00, 0xf4, 0xf8, 0xf5, 0x00, 0xf9, 0xfc, 0xfa, 0x00, 0x00, 0x00, 0x00, 0x00, 0xee, 0xee,
  0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xb0, 0x00,
  0x0a, 0x0e, 0x0a, 0xc0, 0xed, 0x0d, 0xa0, 0xbc, 0xc4, 0x05, 0x02, 0xc0, 0xd7, 0x0d, 0xa0, 0xee,
  0xe3, 0x00, 0x01, 0xb0, 0x80, 0x0d, 0xa0, 0xee, 0xe4, 0x04, 0x03, 0xc0, 0x0e, 0x0c, 0xc0, 0xee,
  0xea, 0x00, 0x0a, 0xe0, 0xee, 0x0e, 0xee, 0xee, 0xee, 0x81, 0x8e, 0xee, 0xee, 0xee, 0xee, 0xee,
  0xee, 0xe7, 0xce, 0xee, 0xee, 0xee, 0xec, 0xbb, 0xce, 0xbb, 0xbd, 0xec, 0xbb, 0xce, 0xd0, 0x00,
  0x6b, 0x00, 0x05, 0xc0, 0x00, 0x6c, 0xd0, 0x99, 0x0c, 0xb9, 0x90, 0xb0, 0x99, 0x0c, 0xd0, 0x00,
  0x6d, 0x40, 0x0b, 0xd0, 0x00, 0x6e, 0xd0, 0x77, 0x0d, 0x07, 0x79, 0xd0, 0x77, 0x0e, 0xe0, 0x00,
  0xee, 0xe0, 0x00, 0xe0, 0x00, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
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
    // add BSB-LAN watermark (remove the following line if you don't like it):
    ".c3:before{position:absolute;z-index:-1;width:100%;height:100%;content:'';opacity:.02;background:url('favicon.svg')no-repeat center}" NEWLINE
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
        "zoom:{" NEWLINE
          "enabled:true," NEWLINE
          "rescale:true," NEWLINE
          "onzoomstart:function(){c.subchart.show()}" NEWLINE
        "}," NEWLINE
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
  "<link rel=\"icon\" href=\"/favicon.svg\">" NEWLINE  // without this, most browsers will try to load /favicon.ico
  // "<link rel=\"icon\" sizes=\"16x16\" href=\"/favicon.ico\">" NEWLINE  // not used by svg capable browser, anyway (?)
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
  "<script>function set(p,d){" NEWLINE
    "var v=document.getElementById('value'+p+'-'+d).value.replace(/\\.$/,'')" NEWLINE
          ".replaceAll(' ','_');" NEWLINE
//          ".replace('---','');" NEWLINE
    "window.open(document.getElementById('main_link').href+'S'+p+'!'+d+'='+v,'_self')" NEWLINE
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
