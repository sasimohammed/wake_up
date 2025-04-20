document.addEventListener('DOMContentLoaded', function () {
  const searchInput = document.querySelector('.search-input');
  const searchButton = document.querySelector('.search-button');
  let allJobs = []; // This will store all jobs for filtering

  // Function to fetch and display jobs with optional search term
  function fetchAndDisplayJobs(searchTerm = '') {
    fetch('jobs.json')
      .then(response => response.json())
      .then(data => {
        allJobs = data;
        const jobContainer = document.querySelector('.jobs');
        jobContainer.innerHTML = '';

        const filteredJobs = searchTerm
          ? data.filter(job =>
            job.title.toLowerCase().includes(searchTerm.toLowerCase()) ||
            job.description.toLowerCase().includes(searchTerm.toLowerCase()) ||
            job.skills.some(skill => skill.toLowerCase().includes(searchTerm.toLowerCase())) ||
            job.location.toLowerCase().includes(searchTerm.toLowerCase()) ||
            (job.category && job.category.toLowerCase().includes(searchTerm.toLowerCase()))
          )
          : data;

        if (filteredJobs.length === 0) {
          jobContainer.innerHTML = `
    <div class="no-results">
      <img src="img/not_found.png" alt="No jobs found">
      <p>No jobs found</p>
    </div>
  `;
          return;
        }

        filteredJobs.forEach(job => {
          const fullStars = Math.floor(job.stars);
          const hasHalfStar = job.stars % 1 >= 0.5;
          const emptyStars = 5 - fullStars - (hasHalfStar ? 1 : 0);

          let starsHTML = '';
          for (let i = 0; i < fullStars; i++) {
            starsHTML += '<i class="bx bxs-star"></i>';
          }
          if (hasHalfStar) {
            starsHTML += '<i class="bx bx-star"></i>';
          }
          for (let i = 0; i < emptyStars; i++) {
            starsHTML += '<i class="bx bx-star"></i>';
          }

          const skillsHTML = job.skills.map(skill => `<span class="keyword">${skill}</span>`).join('');

          const jobCard = `
<a href="#" onclick="showJobDetails('${job.id}')" style="text-decoration: none ;">


            <div class="job_card">
              <h3 class="posted-time">${job.posted}</h3>
              <div class="job-header">
                <h1 class="job-title">${job.title}</h1>
                <div class="job-actions">
                  <i class="bx bx-heart"></i>
                  <i class="bx bx-dislike"></i>
                </div>
              </div>

              <div class="info">
                <div class="client-details">
                  <p><i class="bx bx-badge-check"></i> ${job.paymentVerified ? 'Payment Verified' : 'Not Verified'}</p>
                  <p><i class="bx bx-dollar-circle"></i> $${job.spent} Spent</p>
                  <p><i class="bx bx-map"></i> ${job.location}</p>
                  <p>${starsHTML}</p>
                  <p>${job.stars}</p>
                </div>

                <div class="payment">
                  <p><i class="bx bx-time"></i> Hourly Rate: <strong>${job.rate}</strong></p>
                </div>

                <p class="description">${job.description}</p>

                <div class="key_words">
                  ${skillsHTML}
                </div>

                <p class="proposals"><i class="bx bx-envelope"></i> Proposals: ${job.proposals}</p>
              </div>
            </div>
            </a>
          `;

          jobContainer.innerHTML += jobCard;
        });
      })
      .catch(error => console.error('Error loading jobs:', error));
  }

  // Initial job fetch
  fetchAndDisplayJobs();

  // Listen for "Enter" key in search input
  searchInput.addEventListener('keypress', (e) => {
    if (e.key === 'Enter') {
      const searchTerm = searchInput.value.trim();
      fetchAndDisplayJobs(searchTerm);
    }
  });
});

function showJobDetails(jobId) {
  localStorage.setItem('selectedJobId', jobId);
  window.location.href = `job_details.html?id=${jobId}`;


}


// Handle both user and company sign ups
function handleSignUp(type) {
  // 1. Store the profile type in localStorage
  localStorage.setItem('profileType', type);
  console.log(`${type} sign up selected`);

  // 2. Navigate to the appropriate form
  if (type === 'user') {
    window.location.href = "user_form.html";
  } else if (type === 'company') {
    window.location.href = "company_form.html";
  }
}

// Profile navigation
function navigateToProfile() {
  // 1. Retrieve the stored profile type
  const profileType = localStorage.getItem('profileType');

  // 2. Navigate to the correct profile page
  if (profileType === 'user') {
    window.location.href = "profile.html";
  } else if (profileType === 'company') {
    window.location.href = "company_profile.html";
  } else {
    // 3. Handle case where no type is stored
    alert("Please sign up first");
    window.location.href = "signup.html";
  }
}

document.addEventListener('DOMContentLoaded', () => {
  const valueDisplays = document.querySelectorAll('.stats h3');
  const totalDuration = 2000; // All counters finish in 2 seconds

  valueDisplays.forEach((valueDisplay) => {
    const endValue = parseInt(valueDisplay.getAttribute("data-target"));
    let startTime = null;

    function updateCounter(currentTime) {
      if (!startTime) startTime = currentTime;
      const elapsed = currentTime - startTime;

      const progress = Math.min(elapsed / totalDuration, 1);
      const currentValue = Math.floor(progress * endValue);
      valueDisplay.textContent = currentValue.toLocaleString();

      if (progress < 1) {
        requestAnimationFrame(updateCounter);
      } else {
        valueDisplay.textContent = endValue.toLocaleString();
      }
    }

    requestAnimationFrame(updateCounter);
  });
});


document.addEventListener('DOMContentLoaded', function () {


  document.querySelectorAll('.toggle_form').forEach(button => {
    button.addEventListener('click', () => {
      document.querySelector(".add_form").classList.toggle("active");
    });
  });


  document.getElementById("close_form").addEventListener('click', () => {
    document.querySelector(".add_form").classList.remove("active");
  });
});



  document.querySelectorAll('.signup-form').forEach(form => {
  form.addEventListener('submit', function (e) {
    e.preventDefault();

    const formId = form.getAttribute('id');
    const isCompany = formId === 'company-form';

    const name = form.querySelector('#name, #company-name')?.value.trim();
    const email = form.querySelector('#email, #company-email')?.value.trim();
    const phone = form.querySelector('#phone')?.value.trim();
    const password = form.querySelector('#password')?.value;
    const confirmPassword = form.querySelector('#confirm-password')?.value;

    const emailPattern = /^[^ ]+@[^ ]+\.[a-z]{2,3}$/;

    if (!name || !email || !phone || !password || !confirmPassword) {
      alert('Please fill in all required fields.');
      return;
    }

    if (!email.match(emailPattern)) {
      alert('Please enter a valid email address.');
      return;
    }

    if (password !== confirmPassword) {
      alert('Passwords do not match.');
      return;
    }

    // Extra validations for the company form
    if (isCompany) {
      const industry = form.querySelector('#industry')?.value.trim();
      const location = form.querySelector('#location')?.value.trim();
      const website = form.querySelector('#website')?.value.trim();

      const urlPattern = /^(https?:\/\/)?([\w\d\-]+\.)+\w{2,}(\/.+)?$/;

      if (!industry || !location || !website) {
        alert('Please fill in all company-specific fields.');
        return;
      }

      if (!urlPattern.test(website)) {
        alert('Please enter a valid website URL.');
        return;
      }

      window.location.href = 'company_profile.html';
    } else {
      window.location.href = 'profile.html';
    }
  });
});









