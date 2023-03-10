#include<matrix.h> // à modifier

matrix_t clone_matrix(matrix_t m) {
  matrix_t c = m;
  size_t space=c.row_size*c.col_size*sizeof(double);
  c.values = malloc(space);
  memcpy(c.values, m.values, space);
  return c;
}

matrix_t make_identity_matrix(unsigned n) {
  matrix_t id = make_matrix(n,n);
  unsigned i,j;
  for(i=0; i<n; i++)
    for(j=0; j<n; j++)
      m_set(id, i, j, i==j);
  return id;
}

double m_get(matrix_t m, unsigned i, unsigned j) {
  assert(i<m.row_size && j<m.col_size);
  return m.values[i*m.col_size+j];
}

void m_set(matrix_t m, unsigned i, unsigned j, double x) {
  assert(i<m.row_size && j<m.col_size);
  m.values[i*m.col_size+j] = x;
}

void m_add(matrix_t m, unsigned i, unsigned j, double x) {
  assert(i<m.row_size && j<m.col_size);
  m.values[i*m.col_size+j] += x;
}

/*The following function is internal:*/
void peek_row(const matrix_t *m, unsigned i, vector_t *v) {
  v->size = m->col_size;
  v->values = m->values+i*m->col_size;
}



void m_print(matrix_t m) {
  unsigned i;
  vector_t row;
  for(i=0; i<m.row_size; i++) {
    peek_row(&m, i, &row);
    v_print_h(row);
  }
}

matrix_t make_rotation_matrix(double alpha) {
  matrix_t rot = make_matrix(3,4);
  m_set(rot, 0, 0, cos(alpha));
  m_set(rot, 1, 1, cos(alpha));
  m_set(rot, 0, 1, -sin(alpha));
  m_set(rot, 1, 0, sin(alpha));
  return rot;
}

void free_matrix(matrix_t m){
  free(m.values);
}

vector_t apply(matrix_t m, vector_t v) {
  unsigned i;
  vector_t row, res = make_vector(m.row_size);
  assert(m.col_size == v.size);
  for(i=0; i<res.size; i++) {
    peek_row(&m, i, &row);
    v_set(res, i, scalar_prod(row, v));
  }
  return res;
}