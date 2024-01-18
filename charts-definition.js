// Create the charts when the web page loads
window.addEventListener('load', onload);

function onload(event){
  chartT = createTemperatureChart();
  chartTD = createTDSChart();
  chartP = createPHChart();
}

// Create Temperature Chart
function createTemperatureChart() {
  var chart = new Highcharts.Chart({
    chart:{ 
      renderTo:'chart-temperature',
      type: 'spline' 
    },
    series: [
      {
        name: 'Temperature'
      }
    ],
    title: { 
      text: undefined
    },
    plotOptions: {
      line: { 
        animation: false,
        dataLabels: { 
          enabled: true 
        }
      }
    },
    xAxis: {
      type: 'datetime',
      dateTimeLabelFormats: { second: '%H:%M:%S' }
    },
    yAxis: {
      title: { 
        text: 'Temperature Celsius Degrees' 
      }
    },
    credits: { 
      enabled: false 
    }
  });
  return chart;
}

// Create TDS Chart
function createTDSChart(){
  var chart = new Highcharts.Chart({
    chart:{ 
      renderTo:'chart-tds',
      type: 'spline'  
    },
    series: [{
      name: 'TDS'
    }],
    title: { 
      text: undefined
    },    
    plotOptions: {
      line: { 
        animation: false,
        dataLabels: { 
          enabled: true 
        }
      },
      series: { 
        color: '#50b8b4' 
      }
    },
    xAxis: {
      type: 'datetime',
      dateTimeLabelFormats: { second: '%H:%M:%S' }
    },
    yAxis: {
      title: { 
        text: 'TDS (ppm)' 
      }
    },
    credits: { 
      enabled: false 
    }
  });
  return chart;
}

// Create pH Chart
function createPHChart() {
  var chart = new Highcharts.Chart({
    chart:{ 
      renderTo:'chart-ph',
      type: 'spline'  
    },
    series: [{
      name: 'pH'
    }],
    title: { 
      text: undefined
    },    
    plotOptions: {
      line: { 
        animation: false,
        dataLabels: { 
          enabled: true 
        }
      },
      series: { 
        color: '#A62639' 
      }
    },
    xAxis: {
      type: 'datetime',
      dateTimeLabelFormats: { second: '%H:%M:%S' }
    },
    yAxis: {
      title: { 
        text: 'pH' 
      }
    },
    credits: { 
      enabled: false 
    }
  });
  return chart;
}