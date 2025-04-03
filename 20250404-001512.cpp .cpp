<!DOCTYPE html>
<html lang="hi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>छवि से PNG कन्वर्टर - MultiTools</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">
    <link href="../assets/css/style.css" rel="stylesheet">
    <meta name="description" content="किसी भी छवि को PNG फॉर्मेट में मुफ्त में कन्वर्ट करें। JPG, WEBP, GIF से PNG में तुरंत बदलें।">
</head>
<body>
    <div id="header-container"></div>

    <main class="container my-5">
        <div class="row">
            <div class="col-md-8">
                <h2 class="mb-4">छवि से PNG कन्वर्टर</h2>
                
                <div class="card shadow">
                    <div class="card-body">
                        <div id="dropZone" class="drop-zone">
                            <input type="file" id="imageInput" accept="image/*" class="d-none">
                            <label for="imageInput" class="btn btn-primary mb-3">
                                📁 छवि चुनें
                            </label>
                            <p class="text-muted">या छवि को यहाँ खींचें</p>
                            <img id="preview" class="img-fluid mt-3 d-none">
                        </div>
                        
                        <div class="convert-options mt-4">
                            <button onclick="convertToPNG()" class="btn btn-success">
                                PNG में बदलें
                            </button>
                            <a id="downloadLink" class="btn btn-secondary d-none">
                                डाउनलोड करें
                            </a>
                        </div>
                        
                        <div id="errorAlert" class="alert alert-danger mt-3 d-none"></div>
                    </div>
                </div>
                
                <div class="mt-4">
                    <h4>उपयोग के निर्देश:</h4>
                    <ol>
                        <li>छवि फ़ाइल चुनें या खींचकर छोड़ें</li>
                        <li>पूर्वावलोकन की जाँच करें</li>
                        <li>"PNG में बदलें" बटन क्लिक करें</li>
                        <li>परिवर्तित फ़ाइल डाउनलोड करें</li>
                    </ol>
                </div>
            </div>
            
            <div class="col-md-4">
                <div class="ad-sidebar bg-light p-3 rounded">
                    <h5>विज्ञापन</h5>
                    <div class="ad-content">यहाँ विज्ञापन दिखाई देगा</div>
                </div>
            </div>
        </div>
    </main>

    <div id="footer-container"></div>

    <script src="../assets/js/main.js"></script>
    <script>
        // Drag and Drop Functionality
        const dropZone = document.getElementById('dropZone');
        const imageInput = document.getElementById('imageInput');

        dropZone.addEventListener('dragover', (e) => {
            e.preventDefault();
            dropZone.classList.add('dragging');
        });

        dropZone.addEventListener('dragleave', () => {
            dropZone.classList.remove('dragging');
        });

        dropZone.addEventListener('drop', (e) => {
            e.preventDefault();
            dropZone.classList.remove('dragging');
            const file = e.dataTransfer.files[0];
            handleImage(file);
        });

        imageInput.addEventListener('change', (e) => {
            const file = e.target.files[0];
            handleImage(file);
        });

        function handleImage(file) {
            if (!file.type.startsWith('image/')) {
                showError('कृपया केवल छवि फ़ाइलें चुनें');
                return;
            }

            const reader = new FileReader();
            reader.onload = (e) => {
                const preview = document.getElementById('preview');
                preview.src = e.target.result;
                preview.classList.remove('d-none');
            };
            reader.readAsDataURL(file);
        }

        // Conversion Logic
        function convertToPNG() {
            const preview = document.getElementById('preview');
            if (!preview.src) {
                showError('कृपया पहले एक छवि चुनें');
                return;
            }

            const canvas = document.createElement('canvas');
            const ctx = canvas.getContext('2d');
            
            canvas.width = preview.naturalWidth;
            canvas.height = preview.naturalHeight;
            ctx.drawImage(preview, 0, 0);

            canvas.toBlob((blob) => {
                const url = URL.createObjectURL(blob);
                const downloadLink = document.getElementById('downloadLink');
                downloadLink.href = url;
                downloadLink.download = `converted-${Date.now()}.png`;
                downloadLink.classList.remove('d-none');
            }, 'image/png');
        }

        function showError(message) {
            const errorAlert = document.getElementById('errorAlert');
            errorAlert.textContent = message;
            errorAlert.classList.remove('d-none');
            setTimeout(() => errorAlert.classList.add('d-none'), 5000);
        }
    </script>
</body>
</html>

