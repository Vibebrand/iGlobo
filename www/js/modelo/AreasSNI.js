Ext.regModel('AreasSNI',{
	fields : ['nombreCiencia', 'cantidad']
});

 Ext.regStore({                                                         
       model   : 'AreasSNI',
       storeId : 'AreasSNIStore',
       data : [{
								'nombreCiencia': 'Biología Y Química',
								'cantidad': 0
							},
							{
								'nombreCiencia': 'Biotecnología Y Ciencias Agropecuarias',
								'cantidad': 0
							},
							{
								'nombreCiencia': 'Ciencias Sociales Y Económicas',
								'cantidad': 0
							},
							{
								'nombreCiencia': 'Física, Matemáticas Y Ciencias De La Tierra',
								'cantidad': 0
							},
							{
								'nombreCiencia': 'Humanidades Y Ciencias De La Conducta',
								'cantidad': 0
							},
							{
								'nombreCiencia': 'Ingeniería E Industria',
								'cantidad': 0
							},
							{
								'nombreCiencia': 'Medicina Y Ciencias De La Salud',
								'cantidad': 0
							}
							]
   });