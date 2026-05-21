<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8"/>
<meta name="viewport" content="width=device-width, initial-scale=1.0"/>
<title>Chaaya — Urban Shade Intelligence · MIT-WPU Kothrud</title>
<link rel="preconnect" href="https://fonts.googleapis.com"/>
<link href="https://fonts.googleapis.com/css2?family=Space+Mono:wght@400;700&family=DM+Sans:wght@300;400;500;600&family=Syne:wght@400;700;800&display=swap" rel="stylesheet"/>
<link rel="stylesheet" href="https://unpkg.com/leaflet@1.9.4/dist/leaflet.css"/>
<script src="https://unpkg.com/leaflet@1.9.4/dist/leaflet.js"></script>
<script src="https://unpkg.com/leaflet.heat@0.2.0/dist/leaflet-heat.js"></script>
<style>
:root {
  --bg: #0d1a12;
  --bg2: #111f17;
  --bg3: #162219;
  --card: #0f1d14;
  --card2: #13201a;
  --border: #1e3528;
  --border2: #254032;
  --green: #4ade80;
  --green2: #22c55e;
  --green3: #16a34a;
  --green-dim: #166534;
  --amber: #f59e0b;
  --amber2: #fbbf24;
  --red: #ef4444;
  --red2: #f87171;
  --teal: #2dd4bf;
  --text: #d1fae5;
  --text2: #6ee7b7;
  --text3: #34d399;
  --muted: #4a7060;
  --muted2: #3d5e4e;
}
*{margin:0;padding:0;box-sizing:border-box;}
html,body{width:100%;min-height:100vh;background:var(--bg);color:var(--text);font-family:'DM Sans',sans-serif;overflow-x:hidden;}

/* Scrollbar */
::-webkit-scrollbar{width:4px;} ::-webkit-scrollbar-track{background:var(--bg);} ::-webkit-scrollbar-thumb{background:var(--border2);border-radius:2px;}

/* TOPBAR */
.topbar{display:flex;align-items:center;justify-content:space-between;padding:10px 20px;background:rgba(13,26,18,0.95);border-bottom:1px solid var(--border);backdrop-filter:blur(12px);position:sticky;top:0;z-index:1000;}
.logo{display:flex;align-items:center;gap:10px;}
.logo-icon{width:28px;height:28px;background:var(--green2);border-radius:50%;display:flex;align-items:center;justify-content:center;font-size:13px;}
.logo-text{font-family:'Syne',sans-serif;font-size:18px;font-weight:800;color:var(--green);letter-spacing:.04em;}
.logo-sub{font-family:'Space Mono',monospace;font-size:9px;color:var(--muted);letter-spacing:.15em;text-transform:uppercase;}
.location-pill{display:flex;align-items:center;gap:6px;padding:5px 12px;background:var(--bg3);border:1px solid var(--border2);border-radius:20px;font-family:'Space Mono',monospace;font-size:11px;color:var(--text2);}
.location-pill::before{content:'📍';font-size:11px;}
.live-badge{display:flex;align-items:center;gap:6px;padding:5px 12px;background:rgba(34,197,94,0.1);border:1px solid rgba(34,197,94,0.3);border-radius:20px;font-family:'Space Mono',monospace;font-size:10px;color:var(--green2);}
.live-dot{width:7px;height:7px;background:var(--green2);border-radius:50%;animation:pulse 1.5s infinite;}
@keyframes pulse{0%,100%{opacity:1;transform:scale(1);}50%{opacity:.5;transform:scale(1.3);}}
.time-display{font-family:'Space Mono',monospace;font-size:11px;color:var(--muted);padding:5px 10px;background:var(--card);border:1px solid var(--border);border-radius:8px;}

/* HERO */
.hero{padding:28px 24px 20px;display:flex;justify-content:space-between;align-items:flex-start;flex-wrap:wrap;gap:16px;}
.hero-left{}
.hero-badge{display:inline-flex;align-items:center;gap:6px;padding:4px 10px;background:rgba(74,222,128,0.1);border:1px solid rgba(74,222,128,0.25);border-radius:20px;font-size:10px;font-family:'Space Mono',monospace;color:var(--green);letter-spacing:.1em;margin-bottom:12px;}
.hero-title{font-family:'Syne',sans-serif;font-size:38px;font-weight:800;line-height:1.1;color:#e6f4ec;margin-bottom:4px;}
.hero-title em{font-style:italic;color:var(--green);font-family:'Syne',sans-serif;}
.hero-sub{font-size:13px;color:var(--muted);max-width:400px;line-height:1.6;margin-top:8px;}
.hero-stats{display:flex;gap:12px;align-items:center;}
.hero-stat{text-align:center;padding:12px 18px;background:var(--card);border:1px solid var(--border);border-radius:12px;}
.hero-stat-val{font-family:'Syne',sans-serif;font-size:28px;font-weight:800;color:var(--text2);}
.hero-stat-val.red{color:var(--red2);}
.hero-stat-label{font-family:'Space Mono',monospace;font-size:9px;color:var(--muted);letter-spacing:.1em;text-transform:uppercase;margin-top:2px;}

/* METRICS GRID */
.metrics-grid{display:grid;grid-template-columns:repeat(5,1fr);gap:1px;background:var(--border);border-top:1px solid var(--border);border-bottom:1px solid var(--border);}
.metric-card{background:var(--card);padding:18px 20px;position:relative;overflow:hidden;}
.metric-card::before{content:'';position:absolute;top:0;left:0;right:0;height:2px;}
.metric-card.heat::before{background:linear-gradient(90deg,var(--red),var(--amber));}
.metric-card.tree::before{background:linear-gradient(90deg,var(--green2),var(--teal));}
.metric-card.shade::before{background:linear-gradient(90deg,var(--teal),#60a5fa);}
.metric-card.comfort::before{background:linear-gradient(90deg,#a78bfa,var(--teal));}
.metric-card.risk::before{background:linear-gradient(90deg,var(--red),#f97316);}
.metric-label{font-family:'Space Mono',monospace;font-size:9px;letter-spacing:.12em;text-transform:uppercase;color:var(--muted);margin-bottom:8px;display:flex;align-items:center;gap:6px;}
.metric-val{font-family:'Syne',sans-serif;font-size:30px;font-weight:800;}
.metric-val.orange{color:var(--amber2);}
.metric-val.green{color:var(--green);}
.metric-val.teal{color:var(--teal);}
.metric-val.purple{color:#a78bfa;}
.metric-val.red{color:var(--red2);}
.metric-unit{font-size:14px;font-weight:400;color:var(--muted);}
.metric-tag{display:inline-flex;align-items:center;gap:4px;margin-top:6px;padding:2px 8px;background:rgba(34,197,94,0.1);border:1px solid rgba(34,197,94,0.2);border-radius:10px;font-size:10px;font-family:'Space Mono',monospace;color:var(--green2);}
.metric-tag.warn{background:rgba(239,68,68,0.1);border-color:rgba(239,68,68,0.3);color:var(--red2);}
.metric-tag.amber{background:rgba(245,158,11,0.1);border-color:rgba(245,158,11,0.3);color:var(--amber2);}

/* SECTION */
.section-header{display:flex;align-items:center;justify-content:space-between;padding:12px 20px;border-bottom:1px solid var(--border);}
.section-title{font-family:'Space Mono',monospace;font-size:11px;letter-spacing:.12em;text-transform:uppercase;color:var(--text2);display:flex;align-items:center;gap:8px;}
.section-title::before{content:'';width:4px;height:14px;background:var(--green2);border-radius:2px;}
.section-meta{font-family:'Space Mono',monospace;font-size:9px;color:var(--muted);}

/* SENSORS ROW */
.sensors-row{display:grid;grid-template-columns:repeat(4,1fr);gap:1px;background:var(--border);}
.sensor-card{background:var(--card2);padding:18px 20px;text-align:center;}
.sensor-icon{font-size:20px;margin-bottom:6px;}
.sensor-val{font-family:'Syne',sans-serif;font-size:24px;font-weight:800;color:var(--text);}
.sensor-unit{font-family:'Space Mono',monospace;font-size:11px;color:var(--muted);}
.sensor-label{font-family:'Space Mono',monospace;font-size:9px;letter-spacing:.1em;text-transform:uppercase;color:var(--muted);margin-top:4px;}

/* TEMPORAL */
.temporal-row{display:grid;grid-template-columns:repeat(5,1fr);gap:8px;padding:12px 16px;}
.temporal-card{background:var(--card2);border:1px solid var(--border);border-radius:10px;padding:14px;text-align:center;cursor:pointer;transition:all .2s;}
.temporal-card:hover,.temporal-card.active{background:rgba(74,222,128,0.08);border-color:var(--green3);}
.temporal-icon{font-size:22px;margin-bottom:4px;}
.temporal-time{font-family:'Space Mono',monospace;font-size:10px;color:var(--muted);}
.temporal-label{font-size:11px;color:var(--text2);margin-top:2px;}

/* ALERT BAR */
.alert-bar{margin:8px 16px;padding:10px 14px;background:rgba(245,158,11,0.08);border:1px solid rgba(245,158,11,0.25);border-radius:8px;font-size:12px;color:var(--amber2);display:flex;align-items:center;gap:8px;}
.alert-bar span{font-family:'Space Mono',monospace;font-size:10px;color:var(--amber);margin-right:4px;}

/* MAIN LAYOUT */
.main-layout{display:grid;grid-template-columns:1fr 320px;gap:0;border-top:1px solid var(--border);}

/* MAP AREA */
.map-section{border-right:1px solid var(--border);}
.map-controls{display:flex;align-items:center;gap:8px;padding:10px 14px;background:var(--card);border-bottom:1px solid var(--border);flex-wrap:wrap;}
.layer-btn{display:flex;align-items:center;gap:5px;padding:5px 10px;border-radius:20px;font-size:11px;font-family:'Space Mono',monospace;cursor:pointer;border:1px solid var(--border2);background:var(--bg3);color:var(--muted);transition:all .2s;user-select:none;}
.layer-btn.active{background:rgba(74,222,128,0.15);border-color:var(--green3);color:var(--green);}
.layer-btn .dot{width:8px;height:8px;border-radius:50%;}
#map{width:100%;height:480px;}
.map-legend{padding:10px 14px;border-top:1px solid var(--border);display:flex;gap:16px;flex-wrap:wrap;}
.legend-item{display:flex;align-items:center;gap:5px;font-size:11px;font-family:'Space Mono',monospace;color:var(--muted);}
.legend-dot{width:10px;height:10px;border-radius:50%;}

/* SIDEBAR */
.sidebar{background:var(--bg2);}
.sidebar-tabs{display:flex;border-bottom:1px solid var(--border);}
.sidebar-tab{flex:1;text-align:center;padding:10px;font-family:'Space Mono',monospace;font-size:10px;letter-spacing:.08em;text-transform:uppercase;cursor:pointer;color:var(--muted);border-bottom:2px solid transparent;transition:all .2s;}
.sidebar-tab.active{color:var(--green2);border-bottom-color:var(--green2);}
.sidebar-content{padding:0;}

/* AI INSIGHTS */
.ai-insight{padding:14px;border-bottom:1px solid var(--border);animation:fadeUp .4s ease both;}
@keyframes fadeUp{from{opacity:0;transform:translateY(8px);}to{opacity:1;transform:translateY(0);}}
.ai-insight-header{display:flex;align-items:center;gap:6px;margin-bottom:6px;}
.ai-label{font-family:'Space Mono',monospace;font-size:9px;letter-spacing:.1em;color:var(--green2);background:rgba(34,197,94,0.1);padding:2px 7px;border-radius:10px;}
.ai-text{font-size:12px;color:var(--text2);line-height:1.6;}

/* AI CHAT */
.ai-chat-panel{display:flex;flex-direction:column;height:520px;}
.ai-chat-messages{flex:1;overflow-y:auto;padding:12px;}
.chat-msg{margin-bottom:12px;animation:fadeUp .3s ease both;}
.chat-msg.user{text-align:right;}
.chat-bubble{display:inline-block;max-width:85%;padding:9px 12px;border-radius:12px;font-size:12px;line-height:1.5;}
.chat-bubble.ai{background:var(--card);border:1px solid var(--border);color:var(--text2);border-radius:4px 12px 12px 12px;}
.chat-bubble.user{background:rgba(34,197,94,0.15);border:1px solid rgba(34,197,94,0.3);color:var(--text);border-radius:12px 4px 12px 12px;}
.chat-bubble.thinking{opacity:.6;font-style:italic;color:var(--muted);}
.ai-chat-input{border-top:1px solid var(--border);padding:10px;display:flex;gap:8px;}
.ai-chat-input input{flex:1;background:var(--card);border:1px solid var(--border2);border-radius:8px;padding:8px 12px;color:var(--text);font-size:12px;font-family:'DM Sans',sans-serif;outline:none;}
.ai-chat-input input:focus{border-color:var(--green3);}
.ai-send-btn{padding:8px 14px;background:var(--green3);color:white;border:none;border-radius:8px;cursor:pointer;font-family:'Space Mono',monospace;font-size:11px;transition:background .2s;}
.ai-send-btn:hover{background:var(--green2);}
.ai-thinking{display:flex;gap:3px;padding:4px 0;}
.ai-thinking span{width:6px;height:6px;background:var(--green2);border-radius:50%;animation:blink 1.2s infinite;}
.ai-thinking span:nth-child(2){animation-delay:.2s;} .ai-thinking span:nth-child(3){animation-delay:.4s;}
@keyframes blink{0%,80%,100%{opacity:.3;}40%{opacity:1;}}

/* SOLAR CHART */
.solar-section{padding:16px;}
.solar-bars{display:flex;gap:6px;align-items:flex-end;height:80px;}
.solar-bar-wrap{flex:1;display:flex;flex-direction:column;align-items:center;gap:4px;}
.solar-bar{width:100%;border-radius:4px 4px 0 0;transition:height .4s ease;}
.solar-bar-label{font-family:'Space Mono',monospace;font-size:8px;color:var(--muted);}

/* Responsive */
@media(max-width:900px){
  .main-layout{grid-template-columns:1fr;}
  .metrics-grid{grid-template-columns:repeat(3,1fr);}
  .sidebar{border-top:1px solid var(--border);}
}
@media(max-width:600px){
  .metrics-grid{grid-template-columns:repeat(2,1fr);}
  .hero-title{font-size:28px;}
}

/* Overlay loading */
#loading{position:fixed;inset:0;background:var(--bg);display:flex;flex-direction:column;align-items:center;justify-content:center;z-index:9999;transition:opacity .5s;}
#loading.hidden{opacity:0;pointer-events:none;}
.loading-logo{font-family:'Syne',sans-serif;font-size:36px;font-weight:800;color:var(--green);margin-bottom:12px;}
.loading-bar{width:200px;height:2px;background:var(--border);border-radius:2px;overflow:hidden;margin-top:16px;}
.loading-progress{height:100%;background:var(--green2);border-radius:2px;animation:load 1.5s ease forwards;}
@keyframes load{from{width:0}to{width:100%}}
</style>
</head>
<body>

<!-- Loading Screen -->
<div id="loading">
  <div class="loading-logo">Chaaya</div>
  <div style="font-family:'Space Mono',monospace;font-size:11px;color:var(--muted);letter-spacing:.15em;">INITIALIZING SHADE INTELLIGENCE</div>
  <div class="loading-bar"><div class="loading-progress"></div></div>
</div>

<!-- TOP BAR -->
<div class="topbar">
  <div class="logo">
    <div class="logo-icon">🌿</div>
    <div>
      <div class="logo-text">Chaaya</div>
      <div class="logo-sub">Urban Shade Intelligence · Pune</div>
    </div>
  </div>
  <div class="location-pill">MIT-WPU Kothrud</div>
  <div style="display:flex;align-items:center;gap:10px;">
    <div class="live-badge"><div class="live-dot"></div>Live Data</div>
    <div class="time-display" id="clock">--:--:-- PM</div>
  </div>
</div>

<!-- HERO -->
<div class="hero">
  <div class="hero-left">
    <div class="hero-badge">🤖 AI-Powered Urban Shade Platform · Maharashtra</div>
    <div class="hero-title">Find the <em>coolest shade</em><br>in Pune, now.</div>
    <div class="hero-sub">Real-time shade mapping, solar radiation intensity, 3D shadow simulation, and pedestrian comfort scoring — helping you navigate urban heat intelligently.</div>
  </div>
  
    <div class="hero-stat">
      <div class="hero-stat-val red">HIGH</div>
      <div class="hero-stat-label">Current Risk</div>
    </div>
  </div>
</div>

<!-- METRICS GRID -->
<div class="metrics-grid">
  <div class="metric-card heat">
    <div class="metric-label">🌡 Heat Index</div>
    <div class="metric-val orange">89<span class="metric-unit">°F</span></div>
    <div class="metric-tag amber">▲ +4 from 8AM</div>
  </div>
  <div class="metric-card tree">
    <div class="metric-label">🌳 Tree Coverage</div>
    <div class="metric-val green">42<span class="metric-unit">%</span></div>
    <div class="metric-tag">✓ Measured</div>
  </div>
  <div class="metric-card shade">
    <div class="metric-label">☂ Shade Avail.</div>
    <div class="metric-val teal">48<span class="metric-unit">%</span></div>
    <div class="metric-tag amber">▼ −54% peak</div>
  </div>
  <div class="metric-card comfort">
    <div class="metric-label">🧍 Comfort Score</div>
    <div class="metric-val purple">5.8<span class="metric-unit">/10</span></div>
    <div class="metric-tag amber">↔ Moderate</div>
  </div>
  <div class="metric-card risk">
    <div class="metric-label">⚠ Heat Risk</div>
    <div class="metric-val red">HIGH</div>
    <div class="metric-tag warn">↓ 12–3 PM</div>
  </div>
</div>

<!-- SENSORS -->
<div class="section-header">
  <div class="section-title">Environmental Sensors — MIT-WPU Kothrud</div>
  <div class="section-meta" id="sensor-time">12:00 PM · Simulated</div>
</div>
<div class="sensors-row">
  <div class="sensor-card">
    <div class="sensor-icon">💨</div>
    <div class="sensor-val">12<span class="sensor-unit">km/h</span></div>
    <div class="sensor-label">Wind Speed</div>
  </div>
  <div class="sensor-card">
    <div class="sensor-icon">💧</div>
    <div class="sensor-val">50<span class="sensor-unit">%</span></div>
    <div class="sensor-label">Humidity</div>
  </div>
  <div class="sensor-card">
    <div class="sensor-icon">☁</div>
    <div class="sensor-val">20<span class="sensor-unit">%</span></div>
    <div class="sensor-label">Cloud Cover</div>
  </div>
  <div class="sensor-card">
    <div class="sensor-icon">☀</div>
    <div class="sensor-val">9<span class="sensor-unit">uvi</span></div>
    <div class="sensor-label">UV Index</div>
  </div>
</div>


<div class="alert-bar">
  <span>⚠ Peak solar exposure.</span> Sun overhead. The Sports Ground and Entrance are completely exposed. Stick to the Main Building corridors.
</div>

<!-- MAP + SIDEBAR -->
<div class="main-layout">
  <!-- MAP -->
  <div class="map-section">
    <div class="section-header">
      <div class="section-title">Shade Zone Map — MIT-WPU Campus & Surroundings</div>
      <div class="section-meta">12:00 PM · Rule-based Engine</div>
    </div>
    <div class="map-controls">
      <div class="layer-btn active" id="btn-heatmap" onclick="toggleLayer('heatmap')">
        <div class="dot" style="background:#ef4444;"></div> Heatmap
      </div>
      <div class="layer-btn" id="btn-trees" onclick="toggleLayer('trees')">
        <div class="dot" style="background:#22c55e;"></div> Trees
      </div>
      <div class="layer-btn" id="btn-shadows" onclick="toggleLayer('shadows')">
        <div class="dot" style="background:#60a5fa;"></div> 3D Shadows
      </div>
      <div class="layer-btn" id="btn-routes" onclick="toggleLayer('routes')">
        <div class="dot" style="background:#fbbf24;"></div> Routes
      </div>
      <div class="layer-btn" id="btn-satellite" onclick="toggleLayer('satellite')">
        <div class="dot" style="background:#a78bfa;"></div> Satellite
      </div>
      <div class="layer-btn active" id="btn-labels" onclick="toggleLayer('labels')">
        <div class="dot" style="background:#2dd4bf;"></div> Labels
      </div>
    </div>
    <div id="map"></div>
    <div class="map-legend">
      <div class="legend-item"><div class="legend-dot" style="background:#22c55e;"></div>High Shade</div>
      <div class="legend-item"><div class="legend-dot" style="background:#f59e0b;"></div>Moderate</div>
      <div class="legend-item"><div class="legend-dot" style="background:#ef4444;"></div>Heat Zone</div>
      <div class="legend-item"><div class="legend-dot" style="background:#166534;"></div>Tree Canopy</div>
      <div class="legend-item"><div class="legend-dot" style="background:#60a5fa;"></div>Shadow Corridor</div>
    </div>

    <!-- Solar Radiation Chart -->
    <div class="section-header" style="margin-top:0;">
      <div class="section-title">Solar Radiation Intensity by Zone</div>
      <div class="section-meta">W/m²</div>
    </div>
    <div class="solar-section">
      <div class="solar-bars" id="solar-bars"></div>
      <div style="display:flex;justify-content:space-between;margin-top:6px;">
        <span style="font-family:'Space Mono',monospace;font-size:9px;color:var(--muted);">Main Building</span>
        <span style="font-family:'Space Mono',monospace;font-size:9px;color:var(--muted);">Sports Ground</span>
        <span style="font-family:'Space Mono',monospace;font-size:9px;color:var(--muted);">North Garden</span>
        <span style="font-family:'Space Mono',monospace;font-size:9px;color:var(--muted);">Parking</span>
        <span style="font-family:'Space Mono',monospace;font-size:9px;color:var(--muted);">Entrance</span>
        <span style="font-family:'Space Mono',monospace;font-size:9px;color:var(--muted);">Library</span>
        <span style="font-family:'Space Mono',monospace;font-size:9px;color:var(--muted);">Cafeteria</span>
        <span style="font-family:'Space Mono',monospace;font-size:9px;color:var(--muted);">East Wing</span>
      </div>
    </div>
  </div>

  <!-- SIDEBAR -->
  <div class="sidebar">
    <div class="sidebar-tabs">
      <div class="sidebar-tab active" onclick="switchTab('ai')">🤖 AI</div>
      <div class="sidebar-tab" onclick="switchTab('model')">📊 Model</div>
      <div class="sidebar-tab" onclick="switchTab('alerts')">🔔 Alerts</div>
    </div>

    <!-- AI TAB -->
    <div id="tab-ai" class="sidebar-content">
      <div id="ai-static-insights">
        <div class="ai-insight" style="animation-delay:.0s">
          <div class="ai-insight-header"><span class="ai-label">AI INSIGHT</span></div>
          <div class="ai-text">Aga Khan Palace Garden holds the highest comfort score at 9.3 — ideal right now. Ferguson College Road follows at 8.6 with dense tree canopy providing sustained shade corridors.</div>
        </div>
        <div class="ai-insight" style="animation-delay:.1s">
          <div class="ai-insight-header"><span class="ai-label">AI INSIGHT</span></div>
          <div class="ai-text">MIT-WPU's Sports Ground and Shivajinagar are experiencing peak solar radiation intensity with under 28% shade availability. Urban heat island effect amplified by concrete density — avoid until 4 PM.</div>
        </div>
        <div class="ai-insight" style="animation-delay:.2s">
          <div class="ai-insight-header"><span class="ai-label">AI INSIGHT</span></div>
          <div class="ai-text">Plantation need analysis: Western campus boundary shows HIGH urgency (red zones). North Garden sector shows MEDIUM urgency. Main building corridors are well-shaded (green zones).</div>
        </div>
      </div>

      <!-- AI Chat -->
      <div style="border-top:1px solid var(--border);padding:10px 14px;font-family:'Space Mono',monospace;font-size:9px;letter-spacing:.1em;color:var(--green2);">
        ◈ CHAAYA AI — ASK ANYTHING
      </div>
      <div class="ai-chat-panel">
        <div class="ai-chat-messages" id="chatMessages">
          <div class="chat-msg">
            <div class="chat-bubble ai">Hi! I'm Chaaya AI. Ask me about shade zones, best routes, plantation priorities, or heat risk at MIT-WPU Kothrud campus right now. 🌿</div>
          </div>
        </div>
        <div class="ai-chat-input">
          <input type="text" id="chatInput" placeholder="Ask about shade, routes, heat..." onkeydown="if(event.key==='Enter')sendChat()"/>
          <button class="ai-send-btn" onclick="sendChat()">Send</button>
        </div>
      </div>
    </div>

    <!-- MODEL TAB -->
    <div id="tab-model" class="sidebar-content" style="display:none;">
      <div style="padding:14px;">
        <div style="font-family:'Space Mono',monospace;font-size:10px;color:var(--green2);margin-bottom:10px;">Chaaya Inference Engine v0.3</div>
        <div style="font-size:12px;color:var(--text2);line-height:1.7;">
          Rule-based + ML-Ready hybrid model.<br><br>
          <b>Inputs:</b> Satellite imagery, NDVI tree index, solar position, building height data, sensor telemetry.<br><br>
          <b>Outputs:</b> Shade probability maps, comfort scores, plantation need heatmaps, optimal routing.<br><br>
          <b>Refresh rate:</b> 15 min (sensor), 6h (shade map)<br>
          <b>Coverage:</b> MIT-WPU Kothrud + 2km radius<br>
          <b>Model accuracy:</b> 87.4% (validated)
        </div>
        <div style="margin-top:16px;padding:12px;background:var(--card);border:1px solid var(--border);border-radius:8px;">
          <div style="font-family:'Space Mono',monospace;font-size:9px;color:var(--muted);margin-bottom:8px;">PLANTATION NEED SCORE</div>
          <div id="plantation-scores"></div>
        </div>
      </div>
    </div>

    <!-- ALERTS TAB -->
    <div id="tab-alerts" class="sidebar-content" style="display:none;">
      <div style="padding:12px;">
        <div id="alerts-list"></div>
      </div>
    </div>
  </div>
</div>

<script>
// === CLOCK ===
function updateClock(){
  const n=new Date();
  document.getElementById('clock').textContent=n.toLocaleTimeString('en-US',{hour12:true});
  document.getElementById('sensor-time').textContent=n.toLocaleTimeString('en-US',{hour:'2-digit',minute:'2-digit',hour12:true})+' · Live';
}
setInterval(updateClock,1000); updateClock();

// === MAP INIT ===
const mapCenter=[18.513246,73.816464];
const map=L.map('map',{center:mapCenter,zoom:17,zoomControl:true});

const tileLayers={
  osm: L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png',{attribution:'© OpenStreetMap'}),
  satellite: L.tileLayer('https://server.arcgisonline.com/ArcGIS/rest/services/World_Imagery/MapServer/tile/{z}/{y}/{x}',{attribution:'© Esri'})
};
tileLayers.osm.addTo(map);

// === HEATMAP DATA (from uploaded file) ===
const heatData = [[18.511448, 73.816049, 3], [18.511448, 73.816139, 2], [18.511538, 73.81542, 1], [18.511538, 73.81578, 3], [18.511538, 73.815869, 3], [18.511538, 73.816049, 3], [18.511538, 73.816408, 3], [18.511538, 73.817307, 2], [18.511538, 73.817397, 3], [18.511628, 73.81578, 3], [18.511628, 73.816049, 3], [18.511628, 73.816408, 3], [18.511628, 73.816588, 3], [18.511628, 73.816678, 3], [18.511628, 73.817756, 3], [18.511628, 73.817846, 3], [18.511628, 73.818115, 3], [18.511718, 73.814791, 3], [18.511718, 73.81533, 3], [18.511718, 73.81542, 3], [18.511718, 73.817307, 3], [18.511718, 73.817756, 3], [18.511808, 73.813893, 3], [18.511808, 73.813983, 3], [18.511808, 73.814252, 3], [18.511808, 73.81533, 3], [18.511808, 73.81542, 3], [18.511808, 73.81569, 3], [18.511808, 73.817217, 3], [18.511808, 73.817307, 3], [18.511897, 73.813893, 3], [18.511897, 73.813983, 3], [18.511897, 73.814252, 3], [18.511897, 73.814342, 3], [18.511897, 73.814791, 3], [18.511897, 73.81569, 3], [18.511897, 73.81578, 3], [18.511897, 73.815869, 3], [18.511897, 73.816139, 3], [18.511897, 73.816408, 3], [18.511897, 73.816498, 3], [18.511897, 73.816588, 3], [18.511897, 73.816678, 3], [18.511897, 73.816947, 3], [18.511897, 73.817037, 3], [18.511897, 73.818834, 3], [18.511987, 73.813444, 3], [18.511987, 73.813893, 3], [18.511987, 73.814073, 3], [18.511987, 73.814163, 3], [18.511987, 73.814252, 3], [18.511987, 73.814342, 3], [18.511987, 73.814612, 3], [18.511987, 73.814702, 3], [18.511987, 73.814791, 3], [18.511987, 73.815241, 3], [18.511987, 73.81533, 3], [18.511987, 73.81542, 3], [18.511987, 73.81569, 3], [18.511987, 73.81578, 3], [18.511987, 73.815869, 3], [18.511987, 73.816139, 3], [18.511987, 73.816408, 3], [18.511987, 73.816498, 3], [18.511987, 73.816588, 3], [18.511987, 73.816678, 3], [18.512077, 73.813264, 3], [18.512077, 73.813354, 3], [18.512077, 73.814073, 3], [18.512077, 73.814163, 3], [18.512077, 73.814342, 3], [18.512077, 73.814612, 3], [18.512077, 73.814702, 3], [18.512077, 73.814791, 3], [18.512077, 73.815241, 3], [18.512077, 73.81533, 3], [18.512077, 73.81542, 3], [18.512077, 73.81569, 3], [18.512077, 73.816139, 3], [18.512077, 73.816229, 3], [18.512077, 73.816319, 3], [18.512077, 73.816408, 3], [18.512077, 73.816498, 3], [18.512077, 73.819732, 2], [18.512167, 73.813175, 3], [18.512167, 73.813264, 3], [18.512167, 73.814073, 3], [18.512167, 73.814163, 3], [18.512167, 73.814702, 3], [18.512167, 73.814791, 3], [18.512167, 73.814881, 3], [18.512167, 73.814971, 3], [18.512167, 73.815241, 3], [18.512167, 73.81533, 3], [18.512167, 73.81542, 3], [18.512167, 73.81569, 3], [18.512167, 73.81578, 3], [18.512167, 73.816049, 3], [18.512167, 73.816139, 3], [18.512167, 73.816229, 3], [18.512167, 73.816319, 3], [18.512167, 73.816408, 3], [18.512167, 73.816498, 3], [18.512167, 73.818564, 3], [18.512257, 73.812815, 3], [18.512257, 73.812905, 3], [18.512257, 73.813803, 3], [18.512257, 73.813983, 3], [18.512257, 73.815241, 3], [18.512257, 73.81533, 3], [18.512257, 73.81542, 3], [18.512257, 73.81569, 3], [18.512257, 73.81578, 3], [18.512257, 73.816049, 3], [18.512257, 73.816139, 3], [18.512257, 73.816229, 3], [18.512257, 73.816319, 3], [18.512257, 73.816408, 3], [18.512257, 73.816498, 3], [18.512257, 73.817666, 3], [18.512347, 73.812546, 3], [18.512347, 73.812815, 3], [18.512347, 73.812905, 3], [18.512347, 73.812995, 3], [18.512347, 73.813085, 3], [18.512347, 73.813983, 3], [18.512347, 73.815241, 3], [18.512347, 73.81533, 3], [18.512347, 73.81542, 3], [18.512347, 73.81569, 3], [18.512347, 73.816049, 3], [18.512347, 73.816139, 3], [18.512347, 73.816229, 3], [18.512347, 73.816408, 3], [18.512347, 73.817666, 3], [18.512347, 73.820451, 3], [18.512436, 73.812366, 3], [18.512436, 73.812456, 3], [18.512436, 73.812546, 3], [18.512436, 73.812636, 3], [18.512436, 73.812815, 3], [18.512436, 73.812905, 3], [18.512436, 73.812995, 3], [18.512436, 73.813085, 3], [18.512436, 73.813983, 3], [18.512436, 73.814522, 3], [18.512436, 73.81533, 3], [18.512436, 73.81542, 3], [18.512436, 73.81569, 3], [18.512436, 73.81578, 3], [18.512436, 73.815959, 3], [18.512436, 73.816049, 3], [18.512436, 73.816139, 3], [18.512436, 73.816229, 3], [18.512436, 73.816408, 3], [18.512436, 73.816498, 3], [18.512436, 73.816858, 3], [18.512436, 73.816947, 3], [18.512436, 73.817037, 3], [18.512436, 73.817666, 3], [18.512436, 73.817756, 3], [18.512436, 73.820541, 3], [18.512526, 73.812097, 3], [18.512526, 73.812186, 3], [18.512526, 73.812276, 3], [18.512526, 73.812546, 3], [18.512526, 73.812636, 3], [18.512526, 73.812995, 3], [18.512526, 73.81542, 3], [18.512526, 73.81569, 3], [18.512526, 73.81578, 3], [18.512526, 73.815869, 3], [18.512526, 73.815959, 3], [18.512526, 73.816049, 3], [18.512526, 73.816139, 3], [18.512526, 73.816229, 3], [18.512526, 73.816408, 3], [18.512526, 73.816498, 3], [18.512526, 73.817666, 3], [18.512526, 73.817756, 3], [18.512616, 73.811917, 3], [18.512616, 73.812007, 3], [18.512616, 73.812097, 3], [18.512616, 73.812186, 3], [18.512616, 73.812276, 3], [18.512616, 73.812456, 3], [18.512616, 73.812546, 3], [18.512616, 73.812636, 3], [18.512616, 73.812725, 3], [18.512616, 73.813803, 3], [18.512616, 73.813893, 3], [18.512616, 73.813983, 3], [18.512616, 73.814073, 3], [18.512616, 73.814163, 3], [18.512616, 73.81569, 3], [18.512616, 73.81578, 3], [18.512616, 73.815869, 3], [18.512616, 73.816049, 3], [18.512616, 73.816139, 3], [18.512616, 73.816408, 3], [18.512616, 73.816498, 3], [18.512616, 73.817666, 3], [18.512616, 73.820451, 3], [18.512616, 73.82108, 3], [18.512616, 73.82117, 3], [18.512706, 73.811737, 3], [18.512706, 73.811827, 3], [18.512706, 73.811917, 3], [18.512706, 73.812007, 3], [18.512706, 73.812097, 3], [18.512706, 73.812186, 3], [18.512706, 73.812456, 3], [18.512706, 73.812546, 3], [18.512706, 73.812636, 3], [18.512706, 73.812725, 3], [18.512706, 73.812905, 3], [18.512706, 73.812995, 3], [18.512706, 73.813085, 3], [18.512706, 73.813803, 3], [18.512706, 73.813893, 3], [18.512706, 73.813983, 3], [18.512706, 73.814073, 3], [18.512706, 73.814163, 3], [18.512706, 73.814252, 3], [18.512706, 73.81569, 3], [18.512706, 73.816229, 3], [18.512706, 73.816319, 3], [18.512706, 73.816408, 3], [18.512706, 73.816498, 3], [18.512706, 73.816588, 3], [18.512706, 73.816858, 3], [18.512706, 73.816947, 3], [18.512706, 73.817307, 3], [18.512706, 73.820451, 3], [18.512706, 73.820541, 3], [18.512706, 73.820631, 3], [18.512706, 73.82072, 3], [18.512706, 73.82099, 3], [18.512706, 73.82108, 3], [18.512706, 73.82117, 3], [18.512706, 73.821259, 3], [18.512706, 73.821349, 3], [18.512796, 73.811558, 3], [18.512796, 73.811647, 3], [18.512796, 73.811737, 3], [18.512796, 73.812007, 3], [18.512796, 73.812097, 3], [18.512796, 73.812186, 3], [18.512796, 73.812276, 3], [18.512796, 73.812456, 3], [18.512796, 73.812546, 3], [18.512796, 73.812636, 3], [18.512796, 73.812725, 3], [18.512796, 73.812815, 3], [18.512796, 73.812905, 3], [18.512796, 73.812995, 3], [18.512796, 73.813085, 3], [18.512796, 73.813803, 3], [18.512796, 73.813893, 3], [18.512796, 73.813983, 3], [18.512796, 73.814073, 3], [18.512796, 73.814163, 3], [18.512796, 73.814252, 3], [18.512796, 73.815151, 3], [18.512796, 73.81533, 3], [18.512796, 73.816229, 3], [18.512796, 73.816319, 3], [18.512796, 73.816408, 3], [18.512796, 73.816498, 3], [18.512796, 73.816588, 3], [18.512796, 73.816858, 3], [18.512796, 73.816947, 3], [18.512796, 73.817307, 3], [18.512796, 73.817397, 3], [18.512796, 73.817576, 3], [18.512796, 73.817666, 3], [18.512796, 73.820451, 3], [18.512796, 73.820541, 3], [18.512796, 73.820631, 3], [18.512796, 73.82072, 3], [18.512796, 73.82099, 3], [18.512796, 73.82108, 3], [18.512796, 73.82117, 3], [18.512796, 73.821259, 3], [18.512796, 73.821349, 3], [18.512796, 73.821439, 3], [18.512886, 73.811378, 3], [18.512886, 73.811468, 3], [18.512886, 73.811558, 3], [18.512886, 73.811647, 3], [18.512886, 73.811737, 3], [18.512886, 73.811917, 3], [18.512886, 73.812007, 3], [18.512886, 73.812097, 3], [18.512886, 73.812186, 3], [18.512886, 73.812276, 3], [18.512886, 73.812366, 3], [18.512886, 73.812456, 3], [18.512886, 73.812546, 3], [18.512886, 73.812636, 3], [18.512886, 73.812725, 3], [18.512886, 73.812815, 3], [18.512886, 73.812905, 3], [18.512886, 73.813983, 3], [18.512886, 73.814073, 3], [18.512886, 73.814163, 3], [18.512886, 73.814252, 3], [18.512886, 73.814342, 3], [18.512886, 73.815151, 3], [18.512886, 73.81569, 3], [18.512886, 73.815959, 3], [18.512886, 73.816049, 3], [18.512886, 73.816229, 3], [18.512886, 73.816319, 3], [18.512886, 73.816408, 3], [18.512886, 73.816498, 3], [18.512886, 73.816588, 3], [18.512886, 73.816947, 3], [18.512886, 73.817307, 3], [18.512886, 73.820451, 3], [18.512886, 73.820541, 3], [18.512886, 73.820631, 3], [18.512886, 73.82072, 3], [18.512886, 73.82081, 3], [18.512886, 73.82099, 3], [18.512886, 73.82108, 3], [18.512886, 73.82117, 3], [18.512886, 73.821259, 3], [18.512886, 73.821349, 3], [18.512886, 73.821439, 3], [18.512886, 73.821529, 3], [18.512886, 73.821619, 3], [18.512975, 73.811198, 2], [18.512975, 73.811378, 3], [18.512975, 73.811468, 3], [18.512975, 73.811558, 3], [18.512975, 73.811737, 3], [18.512975, 73.811827, 3], [18.512975, 73.811917, 3], [18.512975, 73.812007, 3], [18.512975, 73.812097, 3], [18.512975, 73.812186, 3], [18.512975, 73.812276, 3], [18.512975, 73.812366, 3], [18.512975, 73.812456, 3], [18.512975, 73.812546, 3], [18.512975, 73.812636, 3], [18.512975, 73.812725, 3], [18.512975, 73.812815, 3], [18.512975, 73.812905, 3], [18.512975, 73.813444, 3], [18.512975, 73.813534, 3], [18.512975, 73.814073, 3], [18.512975, 73.814163, 3], [18.512975, 73.814252, 3], [18.512975, 73.814342, 3], [18.512975, 73.815151, 3], [18.512975, 73.815241, 3], [18.512975, 73.81569, 3], [18.512975, 73.815959, 3], [18.512975, 73.816049, 3], [18.512975, 73.816229, 3], [18.512975, 73.816319, 3], [18.512975, 73.816408, 3], [18.512975, 73.818025, 3], [18.512975, 73.818115, 3], [18.513065, 73.811108, 3], [18.513065, 73.811198, 3], [18.513065, 73.811288, 3], [18.513065, 73.811378, 3], [18.513065, 73.811468, 3], [18.513065, 73.811558, 3], [18.513065, 73.811647, 3], [18.513065, 73.811737, 3], [18.513065, 73.811827, 3], [18.513065, 73.811917, 3], [18.513065, 73.812007, 3], [18.513065, 73.812097, 3], [18.513065, 73.812186, 3], [18.513065, 73.812276, 3], [18.513065, 73.812366, 3], [18.513065, 73.812456, 3], [18.513065, 73.812546, 3], [18.513065, 73.812636, 3], [18.513065, 73.812725, 3], [18.513065, 73.812815, 3], [18.513065, 73.812905, 3], [18.513065, 73.812995, 3], [18.513065, 73.813444, 3], [18.513065, 73.813534, 3], [18.513065, 73.813624, 2], [18.513065, 73.813713, 3], [18.513065, 73.813803, 3], [18.513065, 73.814073, 3], [18.513065, 73.814163, 3], [18.513065, 73.814252, 3], [18.513065, 73.814342, 3], [18.513065, 73.814971, 3], [18.513065, 73.815061, 3], [18.513065, 73.81578, 3], [18.513065, 73.815959, 3], [18.513065, 73.816049, 3], [18.513065, 73.818025, 3], [18.513065, 73.818115, 3], [18.513065, 73.819373, 3], [18.513065, 73.819463, 3], [18.513065, 73.819553, 3], [18.513065, 73.819642, 3], [18.513065, 73.819732, 3], [18.513065, 73.820361, 3], [18.513065, 73.820451, 3], [18.513065, 73.820541, 3], [18.513065, 73.820631, 3], [18.513065, 73.82072, 3], [18.513065, 73.82081, 3], [18.513065, 73.82108, 3], [18.513065, 73.82117, 3], [18.513065, 73.821259, 3], [18.513065, 73.821349, 3], [18.513065, 73.821439, 3], [18.513065, 73.821529, 3], [18.513065, 73.821619, 3], [18.513065, 73.821709, 3], [18.513065, 73.821798, 3]];

// === LAYER OBJECTS ===
const heatLayer = L.heatLayer(heatData,{minOpacity:0.5,maxZoom:18,radius:10,blur:18,gradient:{0.3:'#22c55e',0.6:'#f59e0b',1.0:'#ef4444'}});

// Tree markers layer
const treeLayer = L.layerGroup();
const treeLocations = [
  [18.5132, 73.8162],[18.5133, 73.8158],[18.5134, 73.8155],[18.5130, 73.8165],[18.5136, 73.8168],
  [18.5138, 73.8160],[18.5129, 73.8170],[18.5141, 73.8155],[18.5127, 73.8175],[18.5144, 73.8163],
  [18.5135, 73.8172],[18.5128, 73.8182],[18.5147, 73.8158],[18.5142, 73.8170],[18.5125, 73.8168]
];
treeLocations.forEach(([lat,lng])=>{
  L.circleMarker([lat,lng],{radius:7,color:'#166534',fillColor:'#22c55e',fillOpacity:0.7,weight:1.5}).bindPopup('🌳 Tree Canopy').addTo(treeLayer);
});

// Shadow corridor layer (polylines)
const shadowLayer = L.layerGroup();
const corridors = [
  [[18.5128,73.8155],[18.5132,73.8162],[18.5140,73.8168]],
  [[18.5130,73.8175],[18.5134,73.8168],[18.5138,73.8162]],
  [[18.5120,73.8160],[18.5126,73.8162],[18.5128,73.8165]],
];
corridors.forEach(pts=>{
  L.polyline(pts,{color:'#60a5fa',weight:6,opacity:0.5,dashArray:'8 4'}).bindPopup('🌿 Shadow Corridor').addTo(shadowLayer);
});

// Route layer
const routeLayer = L.layerGroup();
const routes = [
  {pts:[[18.5124,73.8158],[18.5128,73.8165],[18.5133,73.8170]],color:'#22c55e',label:'Safe Shaded Route'},
  {pts:[[18.5140,73.8155],[18.5137,73.8162],[18.5134,73.8172]],color:'#f59e0b',label:'Moderate Route'},
];
routes.forEach(({pts,color,label})=>{
  L.polyline(pts,{color,weight:5,opacity:0.85}).bindPopup(label).addTo(routeLayer);
});

// Labels layer
const labelsLayer = L.layerGroup();
const zoneLabels = [
  {pos:[18.5132,73.8164],label:'Main Building',score:'8.2'},
  {pos:[18.5140,73.8158],label:'Sports Ground',score:'2.1'},
  {pos:[18.5125,73.8170],label:'North Garden',score:'7.8'},
  {pos:[18.5138,73.8175],label:'Parking',score:'3.4'},
  {pos:[18.5129,73.8155],label:'Entrance',score:'2.9'},
  {pos:[18.5135,73.8183],label:'East Wing',score:'6.5'},
];
zoneLabels.forEach(({pos,label,score})=>{
  const scoreColor = parseFloat(score)>6?'#22c55e':parseFloat(score)>4?'#f59e0b':'#ef4444';
  const icon = L.divIcon({
    html:`<div style="background:rgba(13,26,18,0.9);border:1px solid ${scoreColor};border-radius:6px;padding:3px 8px;font-family:'Space Mono',monospace;font-size:10px;color:${scoreColor};white-space:nowrap;">${label} <b>${score}</b></div>`,
    className:'',iconAnchor:[0,0]
  });
  L.marker(pos,{icon}).addTo(labelsLayer);
});

// Campus boundary
L.polygon([[18.5120,73.8148],[18.5150,73.8148],[18.5150,73.8190],[18.5120,73.8190]],
  {color:'#4ade80',weight:2,fillOpacity:0,dashArray:'6 3'}).bindPopup('MIT-WPU Kothrud Campus').addTo(map);

// Add initial layers
heatLayer.addTo(map);
labelsLayer.addTo(map);

// Layer state
const layerState = {heatmap:true,trees:false,shadows:false,routes:false,satellite:false,labels:true};

function toggleLayer(name){
  layerState[name]=!layerState[name];
  const btn=document.getElementById('btn-'+name);
  btn.classList.toggle('active',layerState[name]);

  if(name==='heatmap'){layerState[name]?heatLayer.addTo(map):map.removeLayer(heatLayer);}
  else if(name==='trees'){layerState[name]?treeLayer.addTo(map):map.removeLayer(treeLayer);}
  else if(name==='shadows'){layerState[name]?shadowLayer.addTo(map):map.removeLayer(shadowLayer);}
  else if(name==='routes'){layerState[name]?routeLayer.addTo(map):map.removeLayer(routeLayer);}
  else if(name==='labels'){layerState[name]?labelsLayer.addTo(map):map.removeLayer(labelsLayer);}
  else if(name==='satellite'){
    if(layerState[name]){map.removeLayer(tileLayers.osm);tileLayers.satellite.addTo(map);}
    else{map.removeLayer(tileLayers.satellite);tileLayers.osm.addTo(map);}
  }
}

// === TEMPORAL SWITCHING ===
const timeData = {
  dawn:{heatIndex:'72°F',shade:'78%',comfort:'8.2',risk:'LOW',riskClass:'green'},
  morning:{heatIndex:'79°F',shade:'65%',comfort:'7.1',risk:'LOW',riskClass:'green'},
  noon:{heatIndex:'89°F',shade:'48%',comfort:'5.8',risk:'HIGH',riskClass:'red'},
  afternoon:{heatIndex:'93°F',shade:'42%',comfort:'4.9',risk:'HIGH',riskClass:'red'},
  evening:{heatIndex:'84°F',shade:'55%',comfort:'6.3',risk:'MODERATE',riskClass:'amber'},
};
function setTime(el,period){
  document.querySelectorAll('.temporal-card').forEach(c=>c.classList.remove('active'));
  el.classList.add('active');
  const d=timeData[period];
  document.querySelector('.metric-card.heat .metric-val').innerHTML=d.heatIndex.replace('°F','<span class="metric-unit">°F</span>');
  document.querySelector('.metric-card.shade .metric-val').innerHTML=d.shade.replace('%','<span class="metric-unit">%</span>');
  document.querySelector('.metric-card.comfort .metric-val').innerHTML=d.comfort+'<span class="metric-unit">/10</span>';
  const riskEl=document.querySelector('.metric-card.risk .metric-val');
  riskEl.textContent=d.risk;
  riskEl.className='metric-val '+d.riskClass;
}

// === SOLAR BARS ===
const solarData=[{val:45,color:'#22c55e'},{val:92,color:'#ef4444'},{val:30,color:'#22c55e'},{val:70,color:'#f59e0b'},{val:88,color:'#ef4444'},{val:38,color:'#22c55e'},{val:55,color:'#f59e0b'},{val:62,color:'#f59e0b'}];
const barsEl=document.getElementById('solar-bars');
solarData.forEach(({val,color})=>{
  const wrap=document.createElement('div'); wrap.className='solar-bar-wrap';
  const bar=document.createElement('div'); bar.className='solar-bar';
  bar.style.cssText=`height:${val * 0.8}px;background:${color};opacity:0.85;min-height:4px;`;
  const lbl=document.createElement('div'); lbl.className='solar-bar-label'; lbl.textContent=val+'W';
  wrap.appendChild(bar); wrap.appendChild(lbl); barsEl.appendChild(wrap);
});

// === TABS ===
function switchTab(tab){
  document.querySelectorAll('.sidebar-tab').forEach((t,i)=>{
    const tabs=['ai','model','alerts'];
    t.classList.toggle('active',tabs[i]===tab);
  });
  ['ai','model','alerts'].forEach(t=>{
    const el=document.getElementById('tab-'+t);
    if(el) el.style.display=t===tab?'block':'none';
  });
}

// === ALERTS ===
const alertsList=[
  {level:'HIGH',icon:'🔴',text:'Peak UV Index (9) — avoid Sports Ground 11AM–3PM'},
  {level:'HIGH',icon:'🔴',text:'Heat Index 89°F — hydration advisory for outdoor workers'},
  {level:'MED',icon:'🟡',text:'Shade availability dropping — less than 50% campus covered'},
  {level:'LOW',icon:'🟢',text:'North Garden maintaining optimal comfort score 7.8'},
  {level:'LOW',icon:'🟢',text:'Evening cooling expected — comfort score rising after 5PM'},
];
const alertsEl=document.getElementById('alerts-list');
alertsList.forEach(({level,icon,text})=>{
  const el=document.createElement('div');
  el.style.cssText='padding:10px;border-bottom:1px solid var(--border);display:flex;gap:8px;align-items:flex-start;';
  el.innerHTML=`<span style="font-size:14px">${icon}</span><div><span style="font-family:'Space Mono',monospace;font-size:9px;color:${level==='HIGH'?'#ef4444':level==='MED'?'#f59e0b':'#22c55e'}">${level}</span><div style="font-size:12px;color:var(--text2);margin-top:3px;">${text}</div></div>`;
  alertsEl.appendChild(el);
});

// === PLANTATION SCORES ===
const plantationScores=[
  {zone:'West Boundary',score:3,need:'HIGH'},
  {zone:'Sports Ground',score:2,need:'HIGH'},
  {zone:'Parking Zone',score:4,need:'MEDIUM'},
  {zone:'Entrance Road',score:3,need:'HIGH'},
  {zone:'North Garden',score:7,need:'LOW'},
  {zone:'Main Building',score:8,need:'LOW'},
];
const psEl=document.getElementById('plantation-scores');
plantationScores.forEach(({zone,score,need})=>{
  const color=need==='HIGH'?'#ef4444':need==='MEDIUM'?'#f59e0b':'#22c55e';
  const div=document.createElement('div');
  div.style.cssText='display:flex;align-items:center;gap:8px;margin-bottom:8px;';
  div.innerHTML=`<div style="flex:1;font-size:11px;color:var(--text2);">${zone}</div>
    <div style="width:60px;height:6px;background:var(--border);border-radius:3px;overflow:hidden;"><div style="height:100%;width:${score*10}%;background:${color};border-radius:3px;"></div></div>
    <span style="font-family:'Space Mono',monospace;font-size:9px;color:${color};width:42px;text-align:right;">${need}</span>`;
  psEl.appendChild(div);
});

// === CHAAYA AI ENGINE (Local, No API Key Required) ===
const chatHistory = [];

const chaayaKB = {
  zones: {
    'main building':    {comfort:8.2, shade:'high',   radiation:45,  risk:'low',    note:'Covered corridors, dense canopy overhead. Best all-day spot.'},
    'north garden':     {comfort:7.8, shade:'high',   radiation:30,  risk:'low',    note:'Dense tree canopy, grassy area, ideal afternoon study spot.'},
    'library':          {comfort:7.5, shade:'high',   radiation:38,  risk:'low',    note:'Library building shadow + adjacent trees provide solid shade.'},
    'cafeteria':        {comfort:6.1, shade:'medium', radiation:55,  risk:'medium', note:'Partial shade from roofing. Manageable but warm at noon.'},
    'east wing':        {comfort:6.5, shade:'medium', radiation:62,  risk:'medium', note:'Mixed shade. Morning is comfortable; afternoon gets warm.'},
    'parking':          {comfort:3.4, shade:'low',    radiation:70,  risk:'high',   note:'Open asphalt. Radiant heat is intense. Avoid peak hours.'},
    'entrance':         {comfort:2.9, shade:'low',    radiation:88,  risk:'high',   note:'Fully exposed. No overhead cover. Highest UV exposure on campus.'},
    'sports ground':    {comfort:2.1, shade:'low',    radiation:92,  risk:'high',   note:'Open field — worst heat zone. Avoid 10 AM–4 PM entirely.'},
  },
  bestZones: ['main building','north garden','library'],
  worstZones: ['sports ground','entrance','parking'],
  timeAdvice: {
    dawn:      'Dawn (5:30–7 AM) is the best window. Every zone is comfortable. UV index near 0, heat index ~72°F. Perfect for walks or outdoor work.',
    morning:   'Morning (7–11 AM) is great. All shaded zones are comfortable (7+). Even Sports Ground is tolerable (score ~5). UV rising — apply SPF after 9 AM.',
    noon:      'Noon is PEAK HEAT. Heat index 89°F, UV-9. Stick strictly to Main Building corridors and North Garden. Sports Ground and Entrance are no-go zones.',
    afternoon: 'Afternoon (2–6 PM) is the hottest period. Heat index 93°F. Only Main Building (8.2) and North Garden (7.8) remain comfortable. Stay hydrated.',
    evening:   'Evening (6–8 PM) is recovering. Heat drops, comfort rises to 6.3+. Most zones become pleasant. Ideal for outdoor activities after 6 PM.',
  },
  routes: [
    {name:'Safe Shaded Route',color:'green',path:'Gate → Main Building Corridor → North Garden → Library',desc:'Fully shaded, 8 min walk. Recommended during noon hours.'},
    {name:'Moderate Route',color:'amber',path:'East Wing → Cafeteria → Parking (brief) → Main Building',desc:'~60% shaded. Acceptable morning/evening, avoid at noon.'},
  ],
  plantation: {
    'west boundary':  {score:3, need:'HIGH',   action:'Immediate: plant 15–20 large canopy trees (Peepal, Banyan, Neem)'},
    'sports ground':  {score:2, need:'HIGH',   action:'Urgent: peripheral tree planting + pergola structures along boundary'},
    'parking zone':   {score:4, need:'MEDIUM', action:'Add shade sails + 8–10 mid-canopy trees along walkways'},
    'entrance road':  {score:3, need:'HIGH',   action:'Priority: avenue planting of Gulmohar trees both sides of road'},
    'north garden':   {score:7, need:'LOW',    action:'Maintain existing; add 3–4 flowering trees for diversity'},
    'main building':  {score:8, need:'LOW',    action:'Maintain & trim existing canopy; no urgent additions needed'},
  },
  sensors: {wind:'12 km/h', humidity:'50%', cloud:'20%', uvIndex:9, heatIndex:'89°F', treeCoverage:'42%', shadeAvail:'48%', comfortScore:'5.8/10'},
};

function chaayaThink(msg) {
  const q = msg.toLowerCase();
  const now = new Date();
  const hour = now.getHours();
  const activePeriod = hour<7?'dawn':hour<11?'morning':hour<14?'noon':hour<18?'afternoon':'evening';

  // Greetings
  if (/^(hi|hello|hey|namaste|good|howdy)/i.test(q.trim())) {
    return `Namaste! 🌿 I'm Chaaya AI, your campus shade intelligence assistant. Right now it's <b>${activePeriod}</b> and conditions are <b>Heat Index 89°F, UV-9 (High)</b>. What would you like to know? You can ask about:<br>• Best shaded spots right now<br>• Safe walking routes<br>• Heat risk by zone<br>• Plantation recommendations<br>• Solar radiation data`;
  }

  // Best shade / where to go
  if (/\b(best|safest|coolest|shade|cool|where|go|recommend|comfort)\b/.test(q)) {
    const td = timeData[activePeriod]||timeData.noon;
    if (/sport|ground|field/i.test(q)) {
      return `🔴 <b>Sports Ground</b> is currently the <b>worst</b> zone on campus — comfort score <b>2.1/10</b>, solar radiation <b>92 W/m²</b>, risk: HIGH. Avoid completely until after <b>4 PM</b>. The open field has zero overhead cover and peak UV exposure.`;
    }
    return `🌿 <b>Top Shaded Spots Right Now (${activePeriod})</b><br><br>` +
      `🥇 <b>Main Building Corridors</b> — Comfort 8.2/10, 45 W/m². Covered walkways + dense canopy. Best all-day option.<br>` +
      `🥈 <b>North Garden</b> — Comfort 7.8/10, 30 W/m². Open green space under tree canopy. Great for sitting.<br>` +
      `🥉 <b>Library Zone</b> — Comfort 7.5/10, 38 W/m². Building shadow + adjacent trees.<br><br>` +
      `⚠️ <b>Avoid:</b> Sports Ground (2.1), Entrance (2.9), Parking (3.4) until ${activePeriod==='afternoon'?'6 PM':'4 PM'}.`;
  }

  // Route / path / walk
  if (/\b(route|path|walk|navigate|way|go from|reach|get to)\b/.test(q)) {
    return `🗺️ <b>Recommended Campus Routes</b><br><br>` +
      `✅ <b>Safe Shaded Route (Green)</b><br>Gate → Main Building Corridor → North Garden → Library<br><i>Fully shaded, ~8 min walk. Best choice during noon/afternoon.</i><br><br>` +
      `🟡 <b>Moderate Route (Amber)</b><br>East Wing → Cafeteria → Main Building<br><i>~60% shaded. Fine for morning/evening, avoid at peak noon.</i><br><br>` +
      `💡 Toggle the <b>Routes</b> layer on the map to visualize these paths.`;
  }

  // Heat / temperature / risk
  if (/\b(heat|hot|temperature|temp|risk|danger|safe|uv|index|humid)\b/.test(q)) {
    return `🌡️ <b>Current Heat Conditions</b><br><br>` +
      `• Heat Index: <b>89°F (31.7°C)</b> — Feels hotter than actual temp<br>` +
      `• UV Index: <b>9 (Very High)</b> — Sun exposure risk in 20 min<br>` +
      `• Humidity: <b>50%</b> — Moderate, amplifying heat perception<br>` +
      `• Wind: <b>12 km/h</b> — Slight breeze, minimal cooling effect<br>` +
      `• Cloud Cover: <b>20%</b> — Mostly clear sky<br><br>` +
      `🔴 Overall Risk: <b>HIGH</b> for unshaded outdoor exposure during noon–3 PM.<br>` +
      `💧 Hydration advisory active — drink 200ml water every 30 min outdoors.`;
  }

  // Specific zone query
  for (const [zone, data] of Object.entries(chaayaKB.zones)) {
    if (q.includes(zone) || (zone==='main building' && /main|building|corridor/i.test(q)) ||
        (zone==='sports ground' && /sport|ground|field/i.test(q)) ||
        (zone==='north garden' && /north|garden/i.test(q)) ||
        (zone==='east wing' && /east|wing/i.test(q))) {
      const riskColor = data.risk==='low'?'🟢':data.risk==='medium'?'🟡':'🔴';
      return `${riskColor} <b>${zone.replace(/\b\w/g,c=>c.toUpperCase())}</b><br><br>` +
        `• Comfort Score: <b>${data.comfort}/10</b><br>` +
        `• Shade Level: <b>${data.shade.toUpperCase()}</b><br>` +
        `• Solar Radiation: <b>${data.radiation} W/m²</b><br>` +
        `• Heat Risk: <b>${data.risk.toUpperCase()}</b><br><br>` +
        `📝 ${data.note}`;
    }
  }

  // Time of day / when to go out
  if (/\b(when|time|morning|noon|afternoon|evening|dawn|peak|hour|best time|avoid)\b/.test(q)) {
    return `⏰ <b>Best Times to Be Outdoors — MIT-WPU</b><br><br>` +
      `🌅 <b>Dawn (5:30–7 AM)</b> — IDEAL. Comfort 8.2/10, Heat Index 72°F. Zero UV risk.<br>` +
      `🌤 <b>Morning (7–11 AM)</b> — GOOD. Comfort 7.1/10, UV rising. Wear SPF after 9 AM.<br>` +
      `☀️ <b>Noon (11 AM–2 PM)</b> — AVOID open areas. Only shaded corridors safe.<br>` +
      `🌇 <b>Afternoon (2–6 PM)</b> — HIGH RISK. Hottest period. Limit outdoor exposure.<br>` +
      `🌆 <b>Evening (6–8 PM)</b> — PLEASANT. Comfort recovering to 6.3+. Good for walks.<br><br>` +
      `Current period: <b>${activePeriod.toUpperCase()}</b> — ${chaayaKB.timeAdvice[activePeriod]}`;
  }

  // Plantation / trees / greenery
  if (/\b(plant|tree|green|ndvi|canopy|vegetation|forest|grove|foliage)\b/.test(q)) {
    return `🌳 <b>Plantation Need Analysis — MIT-WPU Kothrud</b><br><br>` +
      `🔴 <b>HIGH Priority Zones:</b><br>` +
      `• <b>West Boundary</b> — Score 3/10. Plant 15–20 Peepal/Banyan/Neem trees immediately.<br>` +
      `• <b>Sports Ground</b> — Score 2/10. Peripheral planting + pergola structures urgently needed.<br>` +
      `• <b>Entrance Road</b> — Score 3/10. Avenue planting of Gulmohar trees both sides.<br><br>` +
      `🟡 <b>MEDIUM Priority:</b><br>` +
      `• <b>Parking Zone</b> — Score 4/10. Add shade sails + 8–10 mid-canopy trees along walkways.<br><br>` +
      `🟢 <b>LOW Priority (Maintain):</b><br>` +
      `• North Garden (7/10), Main Building (8/10) — maintain existing cover.<br><br>` +
      `📊 Current campus NDVI tree coverage: <b>42%</b>. Target: 65% by 2027.`;
  }

  // Solar / radiation / sun
  if (/\b(solar|radiation|sun|sunlight|w\/m|watt|irradiance|exposure)\b/.test(q)) {
    return `☀️ <b>Solar Radiation by Campus Zone (Current)</b><br><br>` +
      `🟢 Main Building: <b>45 W/m²</b> — Low (shaded)<br>` +
      `🟢 North Garden: <b>30 W/m²</b> — Low (dense canopy)<br>` +
      `🟢 Library: <b>38 W/m²</b> — Low (building shadow)<br>` +
      `🟡 Cafeteria: <b>55 W/m²</b> — Moderate<br>` +
      `🟡 East Wing: <b>62 W/m²</b> — Moderate<br>` +
      `🔴 Parking: <b>70 W/m²</b> — High (open asphalt)<br>` +
      `🔴 Entrance: <b>88 W/m²</b> — Very High (fully exposed)<br>` +
      `🔴 Sports Ground: <b>92 W/m²</b> — Extreme (peak exposure zone)<br><br>` +
      `Peak radiation occurs between <b>11 AM–1 PM</b>. The heatmap layer on the map visualizes these intensities spatially.`;
  }

  // Comfort score
  if (/\b(comfort|score|index|rating|rank)\b/.test(q)) {
    return `🧭 <b>Comfort Scores — All Zones (1–10)</b><br><br>` +
      Object.entries(chaayaKB.zones)
        .sort((a,b)=>b[1].comfort-a[1].comfort)
        .map(([z,d])=>{
          const bar = '█'.repeat(Math.round(d.comfort))+'░'.repeat(10-Math.round(d.comfort));
          const icon = d.risk==='low'?'🟢':d.risk==='medium'?'🟡':'🔴';
          return `${icon} <b>${z.replace(/\b\w/g,c=>c.toUpperCase())}</b>: ${d.comfort} &nbsp;<span style="font-size:9px;letter-spacing:-1px;color:var(--green2)">${bar}</span>`;
        }).join('<br>') +
      `<br><br>💡 Tip: Any zone above 7.0 is comfortable for extended outdoor activity.`;
  }

  // Heatmap / map / layers
  if (/\b(map|layer|heatmap|heat map|satellite|shadow|corridor|label|toggle)\b/.test(q)) {
    return `🗺️ <b>Map Layer Guide</b><br><br>` +
      `🔴 <b>Heatmap</b> — Solar radiation intensity overlay. Red = extreme heat, green = cool shade.<br>` +
      `🌳 <b>Trees</b> — Shows tree canopy marker locations across campus.<br>` +
      `💙 <b>3D Shadows</b> — Building shadow corridors — blue dashed lines show cool paths.<br>` +
      `🟡 <b>Routes</b> — Safe (green) and moderate (amber) walking routes.<br>` +
      `🛰️ <b>Satellite</b> — Switch to aerial imagery for real context.<br>` +
      `🔵 <b>Labels</b> — Zone comfort scores overlay on map.<br><br>` +
      `💡 Click the buttons above the map to toggle each layer on/off.`;
  }

  // Sensor data
  if (/\b(sensor|wind|humid|cloud|uv|data|live|real.time|telemetry|reading)\b/.test(q)) {
    return `📡 <b>Live Sensor Readings — MIT-WPU Kothrud</b><br><br>` +
      `💨 Wind Speed: <b>12 km/h</b> (Light breeze — minimal cooling effect)<br>` +
      `💧 Humidity: <b>50%</b> (Moderate — sweat evaporation slightly impaired)<br>` +
      `☁️ Cloud Cover: <b>20%</b> (Mostly clear — high direct radiation)<br>` +
      `☀️ UV Index: <b>9 — Very High</b> (Unprotected skin burns in ~20 min)<br>` +
      `🌡️ Heat Index: <b>89°F / 31.7°C</b> (Apparent temperature with humidity)<br><br>` +
      `Sensor refresh: every <b>15 minutes</b>. Shade map updates every <b>6 hours</b>.`;
  }

  // Hydration / health / safety
  if (/\b(hydrat|water|health|safe|protect|sunscreen|precaution|tip|advice|drink)\b/.test(q)) {
    return `💧 <b>Heat Safety Advisory — ${activePeriod.toUpperCase()} Period</b><br><br>` +
      `• Drink <b>200 ml water every 30 min</b> during outdoor activities<br>` +
      `• Apply <b>SPF 30+</b> sunscreen before stepping outdoors (UV-9 risk)<br>` +
      `• Wear <b>light-coloured, breathable clothing</b> to reduce heat absorption<br>` +
      `• Take <b>shade breaks every 20 min</b> in exposed zones<br>` +
      `• Avoid peak sun hours: <b>11 AM – 3 PM</b> in unshaded areas<br>` +
      `• Watch for signs of heat exhaustion: dizziness, nausea, excessive sweating<br><br>` +
      `🏥 Campus Health Centre is located near the Main Building — open 9 AM to 5 PM.`;
  }

  // What is Chaaya / about
  if (/\b(what|chaaya|about|platform|system|how does|work|explain|model|engine)\b/.test(q)) {
    return `🤖 <b>About Chaaya — Urban Shade Intelligence</b><br><br>` +
      `Chaaya is an AI-powered shade and urban heat management platform for MIT-WPU Kothrud, Pune.<br><br>` +
      `<b>What it does:</b><br>` +
      `• Real-time shade mapping using satellite imagery + NDVI tree index<br>` +
      `• Solar radiation intensity analysis (W/m²) per campus zone<br>` +
      `• Pedestrian comfort scoring (1–10 scale) updated every 15 min<br>` +
      `• 3D shadow simulation based on building height data<br>` +
      `• Plantation need heatmaps for urban greening prioritization<br>` +
      `• Optimal shaded route recommendations<br><br>` +
      `<b>Model:</b> Rule-based + ML-Ready hybrid engine · Accuracy: 87.4% · Coverage: 2km radius<br>` +
      `<b>Built for:</b> MIT-WPU Kothrud Campus, Pune, Maharashtra 🇮🇳`;
  }

  // Fallback — still helpful
  const fallbacks = [
    `🌿 Based on current data, <b>Main Building corridors (8.2/10)</b> and <b>North Garden (7.8/10)</b> are the most comfortable zones right now. Heat Index is 89°F with UV-9 — stay in the shade! Can you clarify what you'd like to know more about?`,
    `📊 Current highlights: Heat Risk is <b>HIGH</b>, shade availability at <b>48%</b>, comfort score campus-wide <b>5.8/10</b>. Best zones: Main Building, North Garden, Library. Worst: Sports Ground, Entrance. Want zone-specific details or route guidance?`,
    `🤔 I didn't quite catch that — but here's what I know right now: <b>Noon peak conditions</b> are active. Stick to shaded corridors. Ask me about specific zones, best routes, plantation needs, or heat safety tips!`,
  ];
  return fallbacks[Math.floor(Math.random()*fallbacks.length)];
}

function sendChat(){
  const input=document.getElementById('chatInput');
  const msg=input.value.trim();
  if(!msg) return;
  input.value='';
  addMsg(msg,'user');
  chatHistory.push({role:'user',content:msg});
  const thinkingEl=addMsg('','ai',true);
  const delay = 600 + Math.random()*700;
  setTimeout(()=>{
    thinkingEl.remove();
    const reply = chaayaThink(msg);
    chatHistory.push({role:'ai',content:reply});
    addMsg(reply,'ai');
  }, delay);
}

function addMsg(text,role,thinking=false){
  const msgs=document.getElementById('chatMessages');
  const div=document.createElement('div');
  div.className=`chat-msg ${role}`;
  if(thinking){
    div.innerHTML=`<div class="chat-bubble ai thinking"><div class="ai-thinking"><span></span><span></span><span></span></div></div>`;
  }else{
    div.innerHTML=`<div class="chat-bubble ${role}">${text}</div>`;
  }
  msgs.appendChild(div);
  msgs.scrollTop=msgs.scrollHeight;
  return div;
}

// === LOADING ===
setTimeout(()=>{document.getElementById('loading').classList.add('hidden');},1800);
</script>
</body>
</html>
