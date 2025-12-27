/* SE CREAN LAS TABLAS */

CREATE TABLE IF NOT EXISTS usuarios(
    username VARCHAR(30) UNIQUE NOT NULL,
    password VARCHAR(20) NOT NULL,
    PRIMARY KEY(username)
    );

CREATE TABLE IF NOT EXISTS recetas(
    nombre VARCHAR(80),
    ingredientes JSON,
    duenio VARCHAR(30) NOT NULL,
    descripcion TEXT,
    imagen VARCHAR(180),
    fecha_creacion TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY(nombre),
    FOREIGN KEY (duenio) REFERENCES usuarios(username)
    );

/* SE INSERTAN VALORES */

INSERT INTO usuarios (username, password) VALUES
    ('main', 'MTIzNA=='),  -- 1234
    ('carlosperez23', 'cGFzc3dvcmQ='), -- password
    ('damian_chef', 'cXdlcnR5'), -- qwerty
    ('laura_m', 'cmF0YXRvdWlsbGU='), -- ratatouille
    ('paula_cocina', 'cGF1NWVzdHJlbGxhcw=='); -- pau5estrellas

INSERT INTO recetas (nombre, ingredientes, duenio, descripcion, imagen) VALUES
    (
        'Spaghetti con salsa de tomate', 
        '{"Spaghetti": "200 gr", "Tomate": "2 unidad", "Ajo": "2 unidad", "Aceite de oliva": "30 ml", "Sal": "1 gr"}', 
        'main', 
        'Fideos con salsa de tomate fresca con aceite de oliva y ajo.',
        'https://imag.bonviveur.com/espaguetis-rojos-con-tomate.jpg'
    ),

    (
        'Sopa de Tomate', 
        '{"Tomate": "4 unidad", "Caldo de pollo": "500 ml", "Cebolla": "1 unidad", "Ajo": "2 unidad", "Aceite de oliva": "30 ml", "Sal": "5 gr", "Pimienta": "2 gr", "Crema": "100 ml"}', 
        'main', 
        'Sopa caliente de tomates frescos con cebolla, ajo, caldo de pollo y un toque de crema.',
        'https://assets.tmecosys.com/image/upload/t_web767x639/img/recipe/ras/Assets/7D232720-0F91-41E1-99D7-9DAC5F413404/Derivates/360431A8-187D-4325-B46F-060CC1F6EDE4.jpg'
    ),

    (
        'Hamburguesa', 
        '{"Pan de hamburguesa": "1 unidad", "Carne": "200 gr", "Queso cheddar": "1 unidad", "Lechuga": "1 unidad", "Tomate": "2 unidad", "Cebolla": "1 unidad"}', 
        'main', 
        'Hamburguesa con carne de res, queso cheddar, lechuga, tomate y cebolla.',
        'https://img.freepik.com/fotos-premium/hamburguesa-lechuga-tomate-cebolla-morada-queso-base-madera-tejido-cuadros-rojos-fondo-negro-espacio-texto_442783-27.jpg'
    ),

    (
        'Churrasco', 
        '{"Carne": "1000 gr", "Ajo": "3 unidad", "Sal": "5 gr"}', 
        'carlosperez23', 
        'Churrasco a la plancha con ajo.',
        'https://osolemio.com.co/181/churrasco-a-la-plancha.jpg'
    ),

    (
        'Brownies de Chocolate', 
        '{"Chocolate": "200 gr", "Manteca": "100 gr", "Azúcar": "200 gr", "Harina": "100 gr", "Huevo": "3 unidad", "Esencia de vainilla": "5 ml"}', 
        'carlosperez23', 
        'Brownies de chocolate con una textura suave y húmeda.',
        'https://www.recetasderechupete.com/wp-content/uploads/2019/11/Brownie-1200x828.jpg'
    );