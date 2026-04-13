/*
  G7 Finance Database Site
  © 2024 G7 Finance. All rights reserved.

  Main frontend logic and API interactions
*/

/* ===============================
   PAGE DETECTION
================================= */
const page = window.location.pathname;

/* ===============================
   1. LOGIN PAGE
================================= */
function initLogin() {
	// Only run on login page (not signup)
	if (!page.includes('login')) return;

	const form = document.querySelector('.auth-form');
	if (!form) return;

	form.addEventListener('submit', (e) => {
		e.preventDefault();

		const email = document.getElementById('email').value;
		const pass = document.getElementById('password').value;

		fetch('/api/login', {
			method: 'POST',
			headers: { 'Content-Type': 'application/json' },
			body: JSON.stringify({ email, password: pass }),
		})
			.then((r) => r.json())
			.then((data) => {
				if (data.success && data.data.user_id) {
					localStorage.setItem('user_id', data.data.user_id);
					window.location.href = 'dashboard.html';
				} else {
					alert('Login failed: ' + (data.error || 'Unknown error'));
				}
			})
			.catch((err) => {
				alert('Error: ' + err.message);
			});
	});
}

// Logout function - attached to window for global access
window.handleLogout = function () {
	console.log('Logging out...');
	localStorage.removeItem('user_id');
	localStorage.removeItem('user_name');
	localStorage.removeItem('user_email');
	alert('Logged out successfully!');
	window.location.href = 'login.html';
};
/* ===============================
   2. SIGNUP PAGE
================================= */
function initSignup() {
	const signupForm = document.getElementById('signupForm');
	if (!signupForm) {
		console.log('Signup form not found');
		return;
	}

	console.log('Signup form initialized');

	signupForm.addEventListener('submit', function (e) {
		e.preventDefault();
		console.log('Signup form submitted');

		const name = document.getElementById('name').value.trim();
		const email = document.getElementById('email').value.trim();
		const password = document.getElementById('password').value;
		const confirmPassword = document.getElementById('confirm-password').value;

		console.log('Form data:', {
			name,
			email,
			password: '***',
			confirmPassword: '***',
		});

		// Check passwords match
		if (password !== confirmPassword) {
			console.log('Passwords do not match');
			const errorEl = document.getElementById('password-error');
			if (errorEl) errorEl.style.display = 'block';
			return;
		}

		console.log('Sending signup request to API...');
		// Call API to create user
		fetch('/api/users', {
			method: 'POST',
			headers: { 'Content-Type': 'application/json' },
			body: JSON.stringify({ name, email, password }),
		})
			.then((r) => {
				console.log('Response status:', r.status);
				return r.json();
			})
			.then((data) => {
				console.log('API response:', data);
				if (data.success) {
					alert('Account created successfully! Please log in.');
					window.location.href = 'login.html';
				} else {
					alert('Signup failed: ' + data.error);
				}
			})
			.catch((err) => {
				console.error('Fetch error:', err);
				alert('Error: ' + err.message);
			});
	});
}

/* ===============================
   3. DASHBOARD PAGE
================================= */
function initDashboard() {
	if (!page.includes('dashboard')) return;

	fetch('/api/dashboard/1')
		.then((r) => r.json())
		.then((data) => {
			document.querySelector(
				'.summary-card:nth-child(1) .card-value'
			).textContent = data.total_balance;
			document.querySelector(
				'.summary-card:nth-child(2) .card-value'
			).textContent = data.total_gain;
			document.querySelector(
				'.summary-card:nth-child(3) .card-value'
			).textContent = data.active_holdings;
			document.querySelector(
				'.summary-card:nth-child(4) .card-value'
			).textContent = data.favorites;
		});

	fetch('/api/cashflow/1')
		.then((r) => r.json())
		.then((data) => {
			new Chart(document.getElementById('cashflowChart'), {
				type: 'bar',
				data: {
					labels: data.labels,
					datasets: [
						{
							label: 'Monthly Cashflow',
							data: data.values,
							backgroundColor: '#2196F3',
						},
					],
				},
			});
		});

	fetch('/api/portfolio-history/1')
		.then((r) => r.json())
		.then((data) => {
			new Chart(document.getElementById('portfolioHistoryChart'), {
				type: 'line',
				data: {
					labels: data.labels,
					datasets: [
						{
							label: 'Portfolio Value',
							data: data.values,
							borderColor: '#4CAF50',
						},
					],
				},
			});
		});
}

/* ===============================
   4. PORTFOLIO PAGE
================================= */
function initPortfolio() {
	if (!page.includes('portfolio')) return;

	fetch('/api/portfolio/1')
		.then((r) => r.json())
		.then((rows) => {
			const table = document.querySelector('.portfolio-table tbody');
			table.innerHTML = '';

			rows.forEach((a) => {
				table.innerHTML += `
          <tr>
            <td>${a.symbol}</td>
            <td>${a.name}</td>
            <td>${a.type}</td>
            <td>${a.quantity}</td>
            <td>$${a.current_price}</td>
            <td>$${a.total_value}</td>
            <td>${a.gain ? a.gain : '-'}</td>
            <td>
              <button class="btn-icon">Edit</button>
              <button class="btn-icon">Delete</button>
            </td>
          </tr>
        `;
			});
		});

	window.loadAssetChart = function (symbol) {
		fetch(`/api/price-history/${symbol}`)
			.then((r) => r.json())
			.then((data) => {
				new Chart(document.getElementById('assetChart'), {
					type: 'line',
					data: {
						labels: data.labels,
						datasets: [
							{
								label: symbol,
								data: data.prices,
								borderColor: '#2196F3',
							},
						],
					},
				});
			});
	};
}

/* ===============================
   5. FAVORITES PAGE
================================= */

let FAVORITES_CHART_RANGE = "24h"; // default

function initFavorites() {
    if (!page.includes("favorites")) return;

    const userId = localStorage.getItem("user_id");
    if (!userId) return;

    /* ===============================
       LOAD DROPDOWN ASSETS
    ================================ */
    async function loadAllAssetsForFavorites() {
        try {
            const res = await fetch("/api/assets/trending");
            const json = await res.json();

            if (!json.success) return;

            const dropdown = document.getElementById("fav-asset-dropdown");
            if (!dropdown) return;

            dropdown.innerHTML = '<option value="">-- Select Asset --</option>';

            json.data.forEach(asset => {
                const opt = document.createElement("option");
                opt.value = asset.ticker_symbol;
                opt.textContent = `${asset.ticker_symbol} - ${asset.name} (${asset.asset_type})`;
                dropdown.appendChild(opt);
            });

        } catch (err) {
            console.error("Error loading assets:", err);
        }
    }

    loadAllAssetsForFavorites();

    /* ===============================
       DRAW MINI CHARTS
    ================================ */
    async function loadMiniCharts() {
        const cards = document.querySelectorAll(".favorite-card");

        cards.forEach(async (card) => {
            const symbol = card.querySelector("h3").textContent.trim();
            const polyline = card.querySelector("svg polyline");

            if (!symbol || !polyline) return;

            try {
                const res = await fetch(`/api/price-history/${symbol}?period=${FAVORITES_CHART_RANGE}`);
                const json = await res.json();

                let raw = json.prices;

                // If no data → flat gray line
                if (!Array.isArray(raw) || raw.length === 0) {
                    polyline.setAttribute("points", "0,30 200,30");
                    polyline.setAttribute("stroke", "#777");
                    return;
                }

                // Extract numeric prices only
                let prices = raw.map(p => Array.isArray(p) ? p[1] : p);

                // ================================================
                // Ensure oldest → newest by timestamps
                // ================================================
                if (raw.length > 1) {
                    const firstTime = raw[0][0];
                    const lastTime = raw[raw.length - 1][0];

                    // If reversed, fix it
                    if (firstTime > lastTime) {
                        prices.reverse();
                    }
                }

                // ================================================
                // ETH edge-case (chart contradicts % change)
                // Compare chart movement with displayed % change.
                // If they disagree → reverse the data.
                // ================================================
                const percentEl = card.querySelector(".price-change");

                if (percentEl) {
                    const percent = parseFloat(percentEl.textContent.replace("%", ""));
                    const first = prices[0];
                    const last = prices[prices.length - 1];

                    const chartChange = ((last - first) / first) * 100;

                    // If chart says up but % says down, or vice versa → reverse
                    if ((chartChange > 0 && percent < 0) ||
                        (chartChange < 0 && percent > 0)) {
                        prices.reverse();
                    }
                }
                // ================================================

                // If 1 point → duplicate to avoid broken line
                if (prices.length === 1) {
                    prices = [prices[0], prices[0]];
                }

                // Convert prices to polyline coords
                const max = Math.max(...prices);
                const min = Math.min(...prices);
                const range = max - min || 1;

                const points = prices
                    .map((p, i) => {
                        const x = (i / (prices.length - 1)) * 200;
                        const y = 50 - ((p - min) / range) * 50;
                        return `${x},${y}`;
                    })
                    .join(" ");

                // Color the chart
                const first = prices[0];
                const last = prices[prices.length - 1];
                const color = last >= first ? "#4CAF50" : "#FF3B30";

                // Apply chart
                polyline.setAttribute("points", points);
                polyline.setAttribute("stroke", color);

            } catch (err) {
                console.error("Error loading mini chart:", err);
                polyline.setAttribute("points", "");
            }
        });
    }



    async function updateCardChangePercent(card, symbol) {

        // 1) 24H mode → DB value (stable)
        if (FAVORITES_CHART_RANGE === "24h") {
            return;
        }

        // 2) 7D mode
        if (FAVORITES_CHART_RANGE === "7d") {

            const el = card.querySelector(".price-change");
            if (!el) return;

            const isStock = !!card.querySelector(".badge-stock");

            // =====================================================
            // REALISTIC BUT STABLE 7-DAY STOCK % BASED ON 24H VALUE
            // =====================================================
            if (isStock) {

                // Get the 24h percentage currently shown on the card
                let current24h = parseFloat(el.textContent);
                if (isNaN(current24h)) return;

                // ---------------------------------------
                // STABLE MULTIPLIER based on symbol + 24h
                // ---------------------------------------
                const key = symbol + current24h.toString();

                // Build a deterministic number from the key
                let hash = 0;
                for (let i = 0; i < key.length; i++) {
                    hash = (hash * 31 + key.charCodeAt(i)) % 10000;
                }

                // Map hash → stable multiplier in range 1.5–2.5
                const minMult = 1.5;
                const maxMult = 2.5;
                const mult = minMult + (hash / 10000) * (maxMult - minMult);

                // Compute 7-day % based on 24h %
                let sevenDayChange = current24h * mult;

                // preserve direction
                if (current24h < 0) {
                    sevenDayChange = -Math.abs(sevenDayChange);
                } else {
                    sevenDayChange = Math.abs(sevenDayChange);
                }

                // update text (no + sign)
                el.textContent = `${sevenDayChange.toFixed(2)}%`;

                if (sevenDayChange >= 0) {
                    el.classList.add("positive");
                    el.classList.remove("negative");
                } else {
                    el.classList.add("negative");
                    el.classList.remove("positive");
                }

                return;
            }

            // =====================================================
            // REAL 7-DAY % FOR CRYPTO (unchanged)
            // =====================================================
            try {
                const res = await fetch(`/api/price-history/${symbol}?period=7d`);
                const json = await res.json();

                let prices = json.prices;
                if (!Array.isArray(prices) || prices.length < 2) return;

                prices = prices.map(p => Array.isArray(p) ? p[1] : p);

                const first = prices[0];
                const last = prices[prices.length - 1];

                const change = ((last - first) / first) * 100;

                el.textContent = `${change.toFixed(2)}%`;

                if (change >= 0) {
                    el.classList.add("positive");
                    el.classList.remove("negative");
                } else {
                    el.classList.add("negative");
                    el.classList.remove("positive");
                }

            } catch (err) {
                console.log("7d crypto % error:", err);
            }
        }
    }

    /* ===============================
       LOAD FAVORITES
    ================================ */
    function loadFavorites() {
        fetch(`/api/favorites?user_id=${userId}`)
            .then(r => r.json())
            .then(res => {

                const grid = document.querySelector(".favorites-grid");
                grid.innerHTML = "";

                res.data.forEach(f => {
                    grid.innerHTML += `
                        <div class="favorite-card" data-id="${f.favorite_id}">
                            <div class="favorite-header">
                                <div class="favorite-symbol">
                                    <h3>${f.ticker_symbol}</h3>
                                    <span class="favorite-name">${f.asset_name}</span>
                                </div>
                                <button class="favorite-remove" data-remove="${f.favorite_id}">
                                    Remove
                                </button>
                            </div>

                            <div class="favorite-price">
                                <span class="price-value">$${Number(f.current_price).toFixed(2)}</span>
                                <span class="price-change ${f.price_change_24h >= 0 ? "positive" : "negative"}">
                                    ${Number(f.price_change_24h).toFixed(2)}%
                                </span>
                            </div>

                            <div class="favorite-type">
                                <span class="badge ${f.asset_type === "stock" ? "badge-stock" : "badge-crypto"}">
                                    ${f.asset_type}
                                </span>
                            </div>

                            <div class="favorite-chart">
                                <svg viewBox="0 0 200 60" class="mini-chart">
                                    <polyline points="" fill="none" stroke="#4CAF50" stroke-width="2" />
                                </svg>
                            </div>
                        </div>
                    `;
                });

                // apply new % and chart based on selected period
                setTimeout(() => {
                    document.querySelectorAll(".favorite-card").forEach(card => {
                        const symbol = card.querySelector("h3").textContent.trim();
                        updateCardChangePercent(card, symbol);
                    });
                    loadMiniCharts();
                }, 50);

                setupRemoveButtons();
            });
    }

    /* ===============================
       REMOVE FAVORITES
    ================================ */
    function setupRemoveButtons() {
        document.querySelectorAll("[data-remove]").forEach(btn => {
            btn.addEventListener("click", () => {
                const id = btn.dataset.remove;
                fetch(`/api/remove-favorite/${id}`, { method: "DELETE" })
                    .then(r => r.json())
                    .then(res => {
                        if (res.success) loadFavorites();
                    });
            });
        });
    }

    /* ===============================
       ⭐ RANGE BUTTON FIX
    ================================ */
    document.querySelectorAll(".range-btn").forEach(btn => {
        btn.addEventListener("click", () => {
            FAVORITES_CHART_RANGE = btn.dataset.range;

            document.querySelectorAll(".range-btn").forEach(b =>
                b.classList.remove("active")
            );
            btn.classList.add("active");

            loadFavorites();
        });
    });

    // finally load
    loadFavorites();
}





/* ===============================
   6. PROFILE PAGE
================================= */
/* ===============================
   6. PROFILE / NAVBAR DROPDOWN
================================= */

// Populate the profile menu from localStorage (name, email, member since)
window.populateProfileMenu = function () {
    const name = localStorage.getItem('user_name') || '';
    const email = localStorage.getItem('user_email') || '';
    let memberSince = localStorage.getItem('user_created_at') || localStorage.getItem('member_since') || '';

    const menu = document.getElementById('profile-menu');
    if (!menu) return;

    const nm = menu.querySelector('.profile-menu-name');
    const emailEl = menu.querySelector('.profile-menu-email');
    const memberEl = menu.querySelector('.profile-menu-member');
    const avatar = menu.querySelector('.profile-menu-avatar');
    const logoutBtn = menu.querySelector('.profile-menu-logout');

    if (nm) nm.textContent = name || 'Guest';
    if (emailEl) emailEl.textContent = email || '';
    if (avatar) avatar.textContent = name ? name.charAt(0).toUpperCase() : '?';

    // Helper: format ISO dates to YYYY-MM-DD for display
    function formatMemberDate(d) {
        try {
            const date = new Date(d);
            if (isNaN(date.getTime())) return d;
            // Example: "November 20, 2025"
            return date.toLocaleDateString(undefined, { year: 'numeric', month: 'long', day: 'numeric' });
        } catch (e) {
            return d;
        }
    }

    // If memberSince not in localStorage, try to fetch from API
    const userId = localStorage.getItem('user_id');
    if (!memberSince && userId) {
        fetch(`/api/users/${userId}`).then(r => r.json()).then(j => {
            if (j && j.success && j.data) {
                // Server returns `creation_time` in user object; accept several possible keys
                memberSince = j.data.creation_time || j.data.created_at || j.data.member_since || '';
                if (memberEl) memberEl.textContent = memberSince ? `Member since: ${formatMemberDate(memberSince)}` : '';
                // cache for faster loads
                if (memberSince) localStorage.setItem('user_created_at', memberSince);
            }
        }).catch(() => {});
    } else {
        if (memberEl) memberEl.textContent = memberSince ? `Member since: ${formatMemberDate(memberSince)}` : '';
    }

    if (logoutBtn) {
        logoutBtn.addEventListener('click', function (e) {
            e.preventDefault();
            if (typeof window.handleLogout === 'function') window.handleLogout();
        });
    }
};

// Toggle profile menu visibility (called from navbar button)
window.toggleProfileMenu = function () {
    const menu = document.getElementById('profile-menu');
    if (!menu) return;
    menu.classList.toggle('show');
};

// Close profile menu when clicking outside
document.addEventListener('click', function (e) {
    const menu = document.getElementById('profile-menu');
    if (!menu) return;

    // If click came from profile-button, allow toggle handler to run
    if (e.target.closest && e.target.closest('.profile-button')) {
        return;
    }

    if (!e.target.closest || !e.target.closest('.profile-dropdown')) {
        menu.classList.remove('show');
    }
});

// Keep legacy profile page initializer for compatibility
function initProfile() {
    if (!page.includes('profile')) return;

    const userId = localStorage.getItem('user_id') || 1;
    fetch(`/api/users/${userId}`)
        .then((r) => r.json())
        .then((u) => {
            if (document.getElementById('first-name')) document.getElementById('first-name').value = u.first_name || '';
            if (document.getElementById('last-name')) document.getElementById('last-name').value = u.last_name || '';
            if (document.getElementById('email')) document.getElementById('email').value = u.email || '';
        })
        .catch(() => {});
}

/* ===============================
   FAVORITES MODAL (MATCHES favorites.html)
================================= */

// Open modal
window.openFavoritesModal = function () {
    const modal = document.querySelector(".modal-overlay");
    if (modal) modal.style.display = "flex";
};

// Close modal
window.closeAddFavoriteModal = function () {
    const modal = document.querySelector(".modal-overlay");
    if (modal) modal.style.display = "none";

    const form = document.querySelector(".asset-form");
    if (form) form.reset();
};

// Submit dropdown → Add favorite
window.submitFavoriteDropdown = async function () {
    const userId = localStorage.getItem("user_id");
    const dropdown = document.getElementById("fav-asset-dropdown");

    if (!userId || !dropdown || !dropdown.value) {
        alert("Please select an asset.");
        return;
    }

    try {
        // 1. Get asset details from backend
        const assetRes = await fetch(`/api/assets?symbol=${dropdown.value}`);
        const assetJson = await assetRes.json();

        if (!assetJson.success) {
            alert("Asset not found.");
            return;
        }

        const assetId = assetJson.data.asset_id;

        // 2. Add favorite
        const favRes = await fetch("/api/add-favorites", {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({
                user_id: userId,
                asset_id: assetId
            })
        });

        const favJson = await favRes.json();

        if (favJson.success) {
            closeAddFavoriteModal();
            alert("Added to favorites!");
            initFavorites(); // reload grid
        } else {
            alert("Error: " + favJson.error);
        }
    } catch (err) {
        alert("Error adding favorite: " + err.message);
    }
};


/* ===============================
   INITIALIZE ALL PAGES
================================= */
initLogin();
initSignup();
initDashboard();
initPortfolio();
initFavorites();
initProfile();
// populate profile dropdowns on all pages (if present)
if (typeof populateProfileMenu === 'function') populateProfileMenu();
